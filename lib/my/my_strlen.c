/*
** EPITECH PROJECT, 2023
** my_strlen
** File description:
** my_strlen
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int len = 0;

    for (int i = 0; str[i]; i++)
        len++;
    return len;
}
