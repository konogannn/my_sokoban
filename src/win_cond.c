/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** win_cond
*/

#include "../include/sokoban.h"

bool is_win(global_t *global)
{
    for (int i = 0; i < global->nb_box; i++)
        if (global->map2d[global->box[i].y][global->box[i].x] != 'O')
            return false;
    return true;
}

bool blk_cpt(global_t *global, int nb)
{
    if (global->map2d[global->box[nb].y - 1][global->box[nb].x] == '#' &&
        global->map2d[global->box[nb].y][global->box[nb].x - 1] == '#')
        return true;
    if (global->map2d[global->box[nb].y - 1][global->box[nb].x] == '#' &&
        global->map2d[global->box[nb].y][global->box[nb].x + 1] == '#')
        return true;
    if (global->map2d[global->box[nb].y + 1][global->box[nb].x] == '#' &&
        global->map2d[global->box[nb].y][global->box[nb].x - 1] == '#')
        return true;
    if (global->map2d[global->box[nb].y + 1][global->box[nb].x] == '#' &&
        global->map2d[global->box[nb].y][global->box[nb].x + 1] == '#')
        return true;
    return false;
}

bool is_blocked(global_t *global)
{
    for (int i = 0; i < global->nb_box; i++)
        if (!(global->map2d[global->box[i].y][global->box[i].x] != 'O' &&
            blk_cpt(global, i)))
            return false;
    return true;
}
