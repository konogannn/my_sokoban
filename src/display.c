/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** display
*/

#include "../include/sokoban.h"

bool is_box(global_t *global, int y, int x)
{
    for (int i = 0; i < global->nb_box; i++)
        if (global->box[i].x == x && global->box[i].y == y)
            return true;
    return false;
}

bool is_player(global_t *global, int y, int x)
{
    if (global->player->x == x && global->player->y == y)
        return true;
    return false;
}

void display_pos(global_t *global, int i, int j)
{
    if (global->map2d[i][j] == '#')
        mvaddch(i, j, '#');
    if (global->map2d[i][j] == 'O' && !is_player(global, i, j) &&
        !is_box(global, i, j))
        mvaddch(i, j, 'O');
    if (global->map2d[i][j] == ' ' && !is_player(global, i, j) &&
        !is_box(global, i, j))
        mvaddch(i, j, ' ');
    if (global->map2d[i][j] != '#' && is_player(global, i, j))
        mvaddch(i, j, 'P');
    if (global->map2d[i][j] != '#' && is_box(global, i, j))
        mvaddch(i, j, 'X');
}

void display_map(global_t *global)
{
    for (int i = 0; i <= global->height; i++)
        for (int j = 0; j <= global->width; j++)
            display_pos(global, i, j);
}
