/*
** EPITECH PROJECT, 2023
** directory.c
** File description:
** directory
*/

#include "server.h"

void pwd_command(clients_t **client)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        write((*client)->ctrl_sock, "257 \"", 6);
        write((*client)->ctrl_sock, cwd, strlen(cwd));
        write((*client)->ctrl_sock, "\" created.\r\n", 12);
    } else
        write((*client)->ctrl_sock, "Error\r\n", 7);
}
