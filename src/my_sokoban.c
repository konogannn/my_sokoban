/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** my_sokoban
*/

#include "../include/sokoban.h"

void destroyer(global_t *global)
{
    for (int i = 0; i < (global->height); i++)
        free(global->map2d[i]);
    free(global->map2d);
    free(global->box);
    free(global->player);
    free(global);
}

static void win_too_small(int width, int height)
{
    int rows = 0;
    int cols = 0;

    while (rows < width || cols < height) {
        clear();
        getmaxyx(stdscr, rows, cols);
        mvaddstr(rows / 2, cols / 2 - (my_strlen(ENL_TERM) / 2), ENL_TERM);
        refresh();
    }
}

static void is_event(global_t *global)
{
    int rows;
    int cols;

    getmaxyx(stdscr, rows, cols);
    if (rows < global->width || cols < global->height)
        win_too_small(global->width, global->height);
    if (is_win(global)) {
        usleep(10000);
        endwin();
        destroyer(global);
        exit(0);
    }
    if (is_blocked(global)) {
        usleep(10000);
        endwin();
        destroyer(global);
        exit(1);
    }
}

void actualize_event(global_t *global, int key)
{
    if (key == 27) {
        endwin();
        destroyer(global);
        exit(5);
    }
    if (key == 32) {
        global->nb_box = 0;
        loader(global);
    }
    usage(global, key);
}

void play(global_t *global)
{
    int key;

    initscr();
    noecho();
    curs_set(false);
    keypad(stdscr, true);
    display_map(global);
    refresh();
    while (true) {
        key = getch();
        actualize_event(global, key);
        clear();
        display_map(global);
        refresh();
        is_event(global);
    }
    endwin();
}

int my_sokoban(global_t *global)
{
    map_loader(global);
    play(global);
    destroyer(global);
    return 0;
}
