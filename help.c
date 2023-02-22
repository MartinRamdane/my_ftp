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
    write((*client)->ctrl_sock, "USER ", 5);
    write((*client)->ctrl_sock, "PASS ", 5);
    write((*client)->ctrl_sock, "CWD ", 4);
    write((*client)->ctrl_sock, "CDUP ", 5);
    write((*client)->ctrl_sock, "QUIT ", 5);
    write((*client)->ctrl_sock, "DELE ", 5);
    write((*client)->ctrl_sock, "PWD ", 4);
    write((*client)->ctrl_sock, "PASV ", 5);
    write((*client)->ctrl_sock, "PORT ", 5);
    write((*client)->ctrl_sock, "HELP ", 5);
    write((*client)->ctrl_sock, "NOOP ", 5);
    write((*client)->ctrl_sock, "RETR ", 5);
    write((*client)->ctrl_sock, "STOR ", 5);
    write((*client)->ctrl_sock, "LIST\r\n", 6);
}
