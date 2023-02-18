/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    if (ac == 2)
        create_server(av[1]);
    return 0;
}
