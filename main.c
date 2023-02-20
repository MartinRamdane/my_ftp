/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"

char *home_dir;

void display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("       port is the port number on which the");
    printf(" server socket listens\n");
    printf("       path is the path to the home directory");
    printf(" for the Anonymous user\n");
}

int main(int ac, char **av)
{
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0) {
            display_help();
            return 0;
        } else
            return 84;
    }
    if (ac != 3)
        return 84;
    home_dir = av[2];
    create_server(av[1]);
    return 0;
}
