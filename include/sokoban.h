/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** sokoban
*/

#pragma once
#include "my.h"
#include "structure.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ENL_TERM "Please enlarge your terminal."

void basic(global_t *global, int key);
void destroyer(global_t *global);
void display_map(global_t *global);
void error_handler(char const *str);
void fill_int_arr(global_t *global, char *line, int y);
global_t *init_struct(char *path);
bool is_blocked(global_t *global);
bool is_content_ok(global_t *global, int var, int nline);
bool is_box(global_t *global, int y, int x);
bool is_player(global_t *global, int y, int x);
bool is_win(global_t *global);
void loader(global_t *global);
void map_loader(global_t *global);
char **mem_alloc_2d_array(int nb_rows, int nb_cols);
int my_sokoban(global_t *global);
void reset_init(global_t *global);
bool is_not_wall_2(global_t *global, int key);
void complex(global_t *global, int key, int index);
void usage(global_t *global, int key);
