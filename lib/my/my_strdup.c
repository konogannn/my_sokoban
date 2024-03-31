/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** my_strdup
*/

#include "../../include/my.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    char *dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    int i = 0;

    for (i = 0; src[i]; i++)
        dest[i] = src[i];
    dest[i] = 0;
    return dest;
}
