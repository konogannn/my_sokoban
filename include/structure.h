/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** structure
*/

#pragma once

typedef struct entity_s {
    int x;
    int y;
} entity_t;

typedef struct global_s {
    char *filepath;
    char **map2d;
    int nb_box;
    int verif_p;
    int verif_o;
    int width;
    int mwidth;
    int height;
    entity_t *player;
    entity_t *box;
} global_t;
