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

int is_player(global_t *global, int y, int x)
{
    if (global->player->x == x && global->player->y == y)
        return true;
    return false;
}

void display_pos(global_t *global, int i , int j)
{
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    if (global->map2d[i][j] == '#') {
        attron(COLOR_PAIR(4));
        mvaddch(i, j, '#');
        attroff(COLOR_PAIR(4));
    }
    if (global->map2d[i][j] == 'O' && !is_player(global, i, j) &&
        !is_box(global, i, j)) {
        attron(COLOR_PAIR(1));
        mvaddch(i, j, 'O');
        attroff(COLOR_PAIR(1));
    }
    if (global->map2d[i][j] == ' ' && !is_player(global, i, j) &&
        !is_box(global, i, j))
        mvaddch(i, j, ' ');
    if (global->map2d[i][j] != '#' && is_box(global, i, j)) {
        attron(COLOR_PAIR(1));
        mvaddch(i, j, 'X');
        attroff(COLOR_PAIR(1));
    }
    if (global->map2d[i][j] != '#' && is_player(global, i, j))
        mvaddch(i, j, 'P');
}

void display_map(global_t *global)
{
    start_color();
    for (int i = 0; i <= global->height; i++)
        for (int j = 0; j <= global->width; j++)
            display_pos(global, i, j);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    mvprintw(global->height + 1, 0, "Player position is (%i, %i)",
        global->player->x, global->player->y);
    attron(COLOR_PAIR(1));
    mvprintw(global->height + 2, 0, "There is %i box(es).", global->nb_box);
    attroff(COLOR_PAIR(1));
}
