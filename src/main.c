/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** main
*/

#include "../include/sokoban.h"

int helper(void)
{
    my_putstr("USAGE\n\t./my_sokoban map\nDESCRIPTION\n");
    my_putstr("\tmap\tfile representing the warehouse map, ");
    my_putstr("containing '#' for walls,\n");
    my_putstr("\t\t'P' for the player, 'X' for boxes and '0' ");
    my_putstr("for storage locations.\n");
    return 0;
}

int main(int ac, char **av)
{
    global_t *global;

    if (ac != 2)
        error_handler("error: invalid amount of argument\n");
    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return helper();
    if (ac == 2) {
        global = init_struct(av[1]);
        my_sokoban(global);
    }
    return 0;
}
