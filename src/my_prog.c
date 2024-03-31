/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** my_prog
*/

#include "../include/sokoban.h"

static bool is_not_wall(global_t *global, int key)
{
    int x = global->player->x;
    int y = global->player->y;

    if (key == KEY_UP)
        y--;
    if (key == KEY_DOWN)
        y++;
    if (key == KEY_LEFT)
        x--;
    if (key == KEY_RIGHT)
        x++;
    if (global->map2d[y][x] == '#' || x >= global->width ||
        y >= global->height)
        return false;
    for (int i = 0; i < global->nb_box; i++)
        if (global->box[i].x == x && global->box[i].y == y)
            return false;
    return true;
}

bool is_not_wall_2(global_t *global, int key)
{
    int x = global->player->x;
    int y = global->player->y;

    if (key == KEY_UP)
        y -= 2;
    if (key == KEY_DOWN)
        y += 2;
    if (key == KEY_LEFT)
        x -= 2;
    if (key == KEY_RIGHT)
        x += 2;
    if (global->map2d[y][x] == '#')
        return false;
    for (int i = 0; i < global->nb_box; i++)
        if (global->box[i].x == x && global->box[i].y == y)
            return false;
    return true;
}

int is_box_dir(global_t *global, int key)
{
    int x = global->player->x;
    int y = global->player->y;

    if (key == KEY_UP)
        y--;
    if (key == KEY_DOWN)
        y++;
    if (key == KEY_LEFT)
        x--;
    if (key == KEY_RIGHT)
        x++;
    for (int i = 0; i < global->nb_box; i++)
        if (global->box[i].x == x && global->box[i].y == y)
            return i;
    return -1;
}

void basic(global_t *global, int key)
{
    if (key == KEY_UP && is_not_wall(global, KEY_UP))
        global->player->y--;
    if (key == KEY_DOWN && is_not_wall(global, KEY_DOWN))
        global->player->y++;
    if (key == KEY_LEFT && is_not_wall(global, KEY_LEFT))
        global->player->x--;
    if (key == KEY_RIGHT && is_not_wall(global, KEY_RIGHT))
        global->player->x++;
}

void complex(global_t *global, int key, int index)
{
    if (key == KEY_UP)
        global->box[index].y--;
    if (key == KEY_DOWN)
        global->box[index].y++;
    if (key == KEY_LEFT)
        global->box[index].x--;
    if (key == KEY_RIGHT)
        global->box[index].x++;
}

void usage(global_t *global, int key)
{
    int index = is_box_dir(global, key);

    if (index != -1)
        if (is_not_wall_2(global, key))
            complex(global, key, index);
    basic(global, key);
}
