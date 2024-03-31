/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/sokoban.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test for my_put_nbr function
Test(libc, my_put_nbr, .init = redirect_all_std)
{
    int nb = -42;
    char *expected_output = "-42";

    my_put_nbr(nb);

    cr_assert_stdout_eq_str(expected_output);
}

// Test for my_putchar function
Test(libc, my_putchar, .init = redirect_all_std)
{
    char *expected_output = "a";

    my_putchar('a');

    cr_assert_stdout_eq_str(expected_output);
}

// Test for my_putstr function
Test(libc, my_putstr, .init = redirect_all_std)
{
    char *input_string = "abcdefghijklmnopqrstuvwxyz";

    int result = my_putstr(input_string);

    cr_assert_stdout_eq_str(input_string);
    cr_assert_eq(result, 0, "Expected return value to be 0");
}

// Test for my_strcmp function
Test(libc, my_strcmp, .init = redirect_all_std)
{
    char *a = "abcd";
    char *b = "abc";

    int result = my_strcmp(a, a);
    cr_assert_eq(result, 0, "Expected return value to be 0");

    int result2 = my_strcmp(a, b);
    cr_assert_neq(result2, 0, "Expected return value to be !0");
}

// Test for my_strcpy function
Test(libc, my_strcpy, .init = redirect_all_std)
{
    char *input_string = "abcdefghijklmnopqrstuvwxyz";

    char *destination_string = malloc(my_strlen(input_string) * sizeof(char));

    destination_string = my_strcpy(destination_string, input_string);

    cr_assert_str_eq(input_string, destination_string, "Expected strings to be equal");

    free(destination_string);
}

// Test for my_strdup function
Test(libc, my_strdup, .init = redirect_all_std)
{
    char *input_string = "abcdefghijklmnopqrstuvwxyz";

    char *destination_string = malloc(my_strlen(input_string) * sizeof(char));

    destination_string = my_strdup(input_string);

    cr_assert_str_eq(input_string, destination_string, "Expected strings to be equal");

    free(destination_string);
}

// Test for init_struct function
Test(my_sokoban, init_struct, .init = redirect_all_std)
{
    char *path = "map/map";    
    global_t *global = init_struct(path);

    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->player, "Expected player structure to be allocated");
    cr_assert_not_null(global->box, "Expected box structure to be allocated");

    cr_assert_str_eq(global->filepath, path, "Expected filepath to be equal");
    cr_assert_not(global->width);
    cr_assert_not(global->height);
    cr_assert_not(global->nb_box);
    cr_assert_not(global->verif_o);
    cr_assert_not(global->verif_p);

    free(global->player);
    free(global->box);
    free(global);
}

// Test for is_box function
Test(my_sokoban, is_box)
{
    global_t *global = malloc(sizeof(global_t));
    global->box = malloc(50 * sizeof(entity_t));
    global->box[0].x = 1;
    global->box[0].y = 2;
    global->nb_box = 1;

    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->box, "Expected box structure to be allocated");
    cr_assert_eq(global->box[0].x, 1, "Expected box x to be 1");
    cr_assert_eq(global->box[0].y, 2, "Expected box y to be 2");

    bool return_true = is_box(global, 2, 1);
    bool return_false = is_box(global, 1, 2);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    cr_assert_eq(return_false, false, "Expected return_false to be false");
}
// Test for is_player function
Test(my_sokoban, is_player)
{
    global_t *global = malloc(sizeof(global_t));
    global->player = malloc(sizeof(entity_t));
    global->player->x = 1;
    global->player->y = 2;

    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->player, "Expected player structure to be allocated");

    cr_assert_eq(global->player->x, 1, "Expected plaver x to be 1");
    cr_assert_eq(global->player->y, 2, "Expected player y to be 2");

    bool return_true = is_player(global, 2, 1);
    bool return_false = is_player(global, 1, 2);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    cr_assert_eq(return_false, false, "Expected return_false to be false");
}

// Test for map_loader function
Test(my_sokoban, map_loader, .init = redirect_all_std)
{
    char *path = "map/map";
    global_t *global = init_struct(path);

    map_loader(global);
    cr_assert_not_null(global->map2d, "Expected map2d array to be allocated");
    cr_assert_eq(global->width, 11, "Expected width to be 11");
    cr_assert_eq(global->height, 10, "Expected height to be 10");
    cr_assert_eq(global->nb_box, 2, "Expected nb_box to be 2");
    cr_assert_eq(global->verif_o, 2, "Expected verif_o to be 2");
    cr_assert_eq(global->verif_p, 1, "Expected verif_p to be 1");
    cr_assert_eq(global->player->x, 4, "Expected x player to be 4");
    cr_assert_eq(global->player->y, 2, "Expected y player to be 2");
    cr_assert_eq(global->box[0].x, 8, "Expected x box 1 to be 8");
    cr_assert_eq(global->box[0].y, 8, "Expected y box 1 to be 8");
    cr_assert_eq(global->box[1].x, 9, "Expected x box 2 to be 9");
    cr_assert_eq(global->box[1].y, 8, "Expected y box 2 to be 8");

    destroyer(global);
}

// Test for is_content_ok function
Test(my_sokoban, is_content_ok)
{
    char *path = "map/map";
    int value = 34;
    global_t *global = init_struct(path);
    cr_assert_not_null(global, "Expected global structure to be allocated");

    bool return_value = is_content_ok(global, value, 0);
    cr_assert_not(return_value);
}

// Test for is_win function
Test(my_sokoban, is_win)
{
    char *path = "map/map";
    global_t *global = init_struct(path);
    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->box, "Expected box structure to be allocated");
    map_loader(global);
    cr_assert_not_null(global->map2d, "Expected map2d array to be allocated");
    cr_assert_eq(global->width, 11, "Expected width to be 11");
    cr_assert_eq(global->height, 10, "Expected height to be 10");
    cr_assert_eq(global->nb_box, 2, "Expected nb_box to be 2");

    int return_false = is_win(global);
    cr_assert_eq(return_false, FALSE, "Expected return_false to be FALSE");
    destroyer(global);

    path = "map/map";
    global = init_struct(path);
    global->map2d = mem_alloc_2d_array(6, 4);
    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->box, "Expected box structure to be allocated");
    
    char initialModel[6][4] = {
        "###",
        "# #",
        "#P#",
        "#O#",
        "###"
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            global->map2d[i][j] = initialModel[i][j];
        }
    }
    global->nb_box = 1;
    global->box[0].x = 1;
    global->box[0].y = 3;

    int return_true = is_win(global);
    cr_assert_eq(return_true, TRUE, "Expected return_true to be TRUE");
    destroyer(global);
}

// Test for is_blocked function
Test(my_sokoban, is_blocked)
{
    char *path = "map/map";
    global_t *global = init_struct(path);
    map_loader(global);

    int return_false = is_blocked(global);
    cr_assert_eq(return_false, false, "Expected return_false to be false");
    destroyer(global);

    path = "map/map";
    global = init_struct(path);
    global->map2d = mem_alloc_2d_array(6, 5);
    cr_assert_not_null(global, "Expected global structure to be allocated");
    cr_assert_not_null(global->box, "Expected box structure to be allocated");
    
    char initialModel[6][5] = {
        "####",
        "#  #",
        "#P #",
        "#O #",
        "####"
    };
    for (int i = 0; i < 6; i++)
        global->map2d[i] = strdup(initialModel[i]);
    global->nb_box = 1;
    global->box[0].x = 1;
    global->box[0].y = 1;

    int return_true = is_blocked(global);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    destroyer(global);
}

Test(my_sokoban, is_blocked2)
{
    global_t *global = init_struct("map/map");

    global->map2d = mem_alloc_2d_array(6, 5);
    
    char initialModel[6][5] = {
        "####",
        "#  #",
        "#PO#",
        "#  #",
        "####"
    };
    for (int i = 0; i < 6; i++)
        global->map2d[i] = strdup(initialModel[i]);
    global->nb_box = 1;
    global->box[0].x = 2;
    global->box[0].y = 1;

    int return_true = is_blocked(global);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    global->box[0].x = 1;
    global->box[0].y = 3;

    return_true = is_blocked(global);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    global->box[0].x = 2;
    global->box[0].y = 3;

    return_true = is_blocked(global);
    cr_assert_eq(return_true, true, "Expected return_true to be true");
    destroyer(global);
}

// Test for is_not_wall function
Test(my_sokoban, is_not_wall)
{
    global_t *global = init_struct("map/map");
    global->map2d = mem_alloc_2d_array(6, 5);

    char initialModel[6][5] = {
        "####",
        "#  #",
        "#PO#",
        "#  #",
        "####"
    };
    for (int i = 0; i < 6; i++)
        global->map2d[i] = strdup(initialModel[i]);
    global->player->x = 2;
    global->player->y = 2;
    global->nb_box = 1;
    global->box[0].x = 2;
    global->box[0].y = 1;

    basic(global, KEY_LEFT);
    cr_assert_eq(global->player->x, 2, "Expected x to be 2");
    cr_assert_eq(global->player->y, 2, "Expected y to be 1");
}

// Test for is_not_wall_2 function
Test(my_sokoban, is_not_wall_2)
{
    global_t *global = init_struct("map/map");
    global->map2d = mem_alloc_2d_array(6, 5);

    char initialModel[6][5] = {
        "####",
        "#  #",
        "#PO#",
        "#  #",
        "####"
    };
    for (int i = 0; i < 6; i++)
        global->map2d[i] = strdup(initialModel[i]);
    global->player->x = 2;
    global->player->y = 2;
    global->nb_box = 1;
    global->box[0].x = 2;
    global->box[0].y = 1;

    bool return_value = is_not_wall_2(global, KEY_UP);
    cr_assert_eq(return_value, false, "Expected return_value to be false");
    return_value = is_not_wall_2(global, KEY_DOWN);
    cr_assert_eq(return_value, false, "Expected return_value to be false");
    return_value = is_not_wall_2(global, KEY_LEFT);
    cr_assert_eq(return_value, false, "Expected return_value to be false");
    return_value = is_not_wall_2(global, KEY_RIGHT);
    cr_assert_eq(return_value, true, "Expected return_value to be true");
    destroyer(global);

    global = init_struct("map/map");
    global->map2d = mem_alloc_2d_array(6, 5);

    char initialModel2[7][5] = {
        "####",
        "#  #",
        "#PO#",
        "#  #",
        "#  #",
        "####"
    };
    for (int i = 0; i < 7; i++)
        global->map2d[i] = strdup(initialModel2[i]);
    global->player->x = 2;
    global->player->y = 2;
    global->nb_box = 1;
    global->box[0].x = 2;
    global->box[0].y = 4;

    return_value = is_not_wall_2(global, KEY_DOWN);
    cr_assert_eq(return_value, false, "Expected return_value to be false");
}

// Test for complex function
Test(my_sokoban, complex)
{
    global_t *global = init_struct("map/map");
    global->map2d = mem_alloc_2d_array(6, 5);

    char initialModel[6][5] = {
        "####",
        "#  #",
        "#PO#",
        "#  #",
        "####"
    };
    for (int i = 0; i < 6; i++)
        global->map2d[i] = strdup(initialModel[i]);
    global->nb_box = 1;
    global->box[0].x = 2;
    global->box[0].y = 1;

    complex(global, KEY_UP, 0);
    cr_assert_eq(global->box[0].x, 2, "Expected x to be 2");
    cr_assert_eq(global->box[0].y, 0, "Expected y to be 0");
    complex(global, KEY_DOWN, 0);
    cr_assert_eq(global->box[0].x, 2, "Expected x to be 2");
    cr_assert_eq(global->box[0].y, 1, "Expected y to be 1");
    complex(global, KEY_LEFT, 0);
    cr_assert_eq(global->box[0].x, 1, "Expected x to be 1");
    cr_assert_eq(global->box[0].y, 1, "Expected y to be 1");
    complex(global, KEY_RIGHT, 0);
    cr_assert_eq(global->box[0].x, 2, "Expected x to be 2");
    cr_assert_eq(global->box[0].y, 1, "Expected y to be 1");
    destroyer(global);
}

// Test for usage function
Test(my_sokoban, usage)
{
    char *path = "map/map";
    global_t *global = init_struct(path);
    map_loader(global);
    cr_assert_not_null(global->map2d, "Expected map2d array to be allocated");
    cr_assert_eq(global->width, 11, "Expected width to be 11");
    cr_assert_eq(global->height, 10, "Expected height to be 10");
    cr_assert_eq(global->nb_box, 2, "Expected nb_box to be 2");
    cr_assert_eq(global->player->x, 4, "P - Expected x to be 8");
    cr_assert_eq(global->player->y, 2, "P - Expected y to be 8");
    cr_assert_eq(global->box[0].x, 8, "B0 - Expected x to be 8");
    cr_assert_eq(global->box[0].y, 8, "B0 - Expected y to be 8");
    cr_assert_eq(global->box[1].x, 9, "B1 - Expected x to be 8");
    cr_assert_eq(global->box[1].y, 8, "B1 - Expected y to be 9");
    usage(global, KEY_UP);
    cr_assert_eq(global->player->x, 4, "P - Expected x to be 4");
    cr_assert_eq(global->player->y, 1, "P - Expected y to be 1");
    usage(global, KEY_DOWN);
    cr_assert_eq(global->player->x, 4, "P - Expected x to be 4");
    cr_assert_eq(global->player->y, 2, "P - Expected y to be 3");
    usage(global, KEY_LEFT);
    cr_assert_eq(global->player->x, 3, "P - Expected x to be 3");
    cr_assert_eq(global->player->y, 2, "P - Expected y to be 2");
    usage(global, KEY_RIGHT);
    cr_assert_eq(global->player->x, 4, "P - Expected x to be 5");
    cr_assert_eq(global->player->y, 2, "P - Expected y to be 2");
    global->player->x = 9;
    global->player->y = 9;
    usage(global, KEY_UP);
    cr_assert_eq(global->player->x, 9, "P - Expected x to be 9");
    cr_assert_eq(global->player->y, 8, "P - Expected y to be 8");
    global->player->x = 9;
    global->player->y = 9;
    usage(global, KEY_UP);
    cr_assert_eq(global->player->x, 9, "P - Expected x to be 9");
    cr_assert_eq(global->player->y, 8, "P - Expected y to be 8");
    global->player->x = 8;
    global->player->y = 7;
    usage(global, KEY_DOWN);
    cr_assert_eq(global->player->x, 8, "P - Expected x to be 8");
    cr_assert_eq(global->player->y, 7, "P - Expected y to be 7");
}
