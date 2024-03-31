/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** open_map
*/

#include "../include/sokoban.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

static void set_player_n_box(global_t *global, char c, int y, int x)
{
    if (c == 'P') {
        global->verif_p++;
        global->player->x = x;
        global->player->y = y;
        global->map2d[y][x] = ' ';
    }
    if (c == 'O')
        global->verif_o++;
    if (c == 'X') {
        global->box[global->nb_box].x = x;
        global->box[global->nb_box].y = y;
        global->nb_box++;
        global->map2d[y][x] = ' ';
    }
}

static void verif(global_t *global, int y)
{
    for (int x = 0; global->map2d[y][x] != '\n'; x++)
        set_player_n_box(global, global->map2d[y][x], y, x);
}

void loader(global_t *global)
{
    FILE *file = fopen(global->filepath, "r");
    char *line = NULL;
    size_t len = 0;
    int y = 0;

    while (getline(&line, &len, file) != -1) {
        global->map2d[y] = my_strdup(line);
        verif(global, y);
        y++;
    }
    if (line)
        free(line);
    fclose(file);
}

char **mem_alloc_2d_array(int nb_rows, int nb_cols)
{
    char **arr = malloc(sizeof(char *) * (nb_rows + 1));

    if (!arr)
        return (NULL);
    for (int i = 0; i < nb_rows; i++) {
        arr[i] = malloc(sizeof(char) * (nb_cols + 2));
        if (!arr[i])
            return NULL;
    }
    arr[nb_rows] = NULL;
    return arr;
}

bool is_content_ok(global_t *global, int var, int pos)
{
    if (var != ' ' && var != '\n' && var != '#' &&
    var != 'X' && var != 'O' && var != 'P' && var != '\0') {
        return false;
    }
    if (var == '\n') {
        global->height++;
        pos = 1;
    } else if (!pos && !global->height)
        global->width++;
    return true;
}

static void is_line_ok(global_t *global, char *line)
{
    int pos = 0;

    for (int i = 0; line[i]; i++)
        if (!is_content_ok(global, line[i], pos))
            error_handler("error: file, invalid content.\n");
}

static void set_dim(global_t *global)
{
    FILE *file = fopen(global->filepath, "r");
    char *line = NULL;
    size_t len = 0;

    if (!file)
        error_handler("error: failed to open file.\n");
    while (getline(&line, &len, file) != -1)
        is_line_ok(global, line);
    global->height--;
    global->width--;
    if (line)
        free(line);
    fclose(file);
}

void map_loader(global_t *global)
{
    set_dim(global);
    if (global->width <= 1 || global->height <= 1)
        error_handler("error: map too small.\n");
    global->map2d = mem_alloc_2d_array(global->height, global->width);
    if (global->map2d == NULL)
        error_handler("error: malloc failed.\n");
    loader(global);
    if (global->verif_p != 1 || global->nb_box != global->verif_o)
        error_handler("error: invalid amount of player or box.\n");
}

void error_handler(char const *str)
{
    write(2, str, my_strlen(str));
    exit(84);
}
