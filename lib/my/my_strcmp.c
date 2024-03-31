/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_strcmp
*/

int my_strcmp(char *a, char *b)
{
    while (*a) {
        if (*a != *b)
            return *a - *b;
        a++;
        b++;
    }
    return *a - *b;
}
