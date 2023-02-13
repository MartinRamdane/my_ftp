/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"
#include "client.h"

int main(int ac, char **av)
{
    if (ac == 2)
        create_server(av[1]);
    else if (ac == 3)
        create_client(av[1], av[2]);
    return 0;
}