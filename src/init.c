/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** init
*/

#include "../include/sokoban.h"

global_t *init_struct(char *path)
{
    global_t *global = malloc(sizeof(global_t));

    global->player = malloc(sizeof(entity_t));
    global->box = malloc(50 * sizeof(entity_t));
    if (!global || !global->player || !global->box)
        error_handler("error: malloc failed.\n");
    global->filepath = path;
    global->width = 0;
    global->height = 0;
    global->nb_box = 0;
    global->verif_o = 0;
    global->verif_p = 0;
    return global;
}
