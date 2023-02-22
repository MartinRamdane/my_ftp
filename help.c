/*
** EPITECH PROJECT, 2023
** help
** File description:
** help.c
*/

#include "server.h"

void help_command(clients_t **client)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    write((*client)->ctrl_sock, "214 Help message.\r\n", 19);
}
