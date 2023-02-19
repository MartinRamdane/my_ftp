/*
** EPITECH PROJECT, 2023
** connexion.c
** File description:
** connexion
*/

#include "server.h"

void user_command(clients_t **client, char *line)
{
    if ((*client)->passwd == 1) {
        write((*client)->ctrl_sock, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    char *username = strchr(line, ' ');
    if (username != NULL)
        username++;
    else {
        write((*client)->ctrl_sock, "Error\r\n", 7);
        return;
    }
    if (strcmp(username, "Anonymous") == 0) {
        write((*client)->ctrl_sock, "331 User name okay, ", 20);
        write((*client)->ctrl_sock, "need password.\r\n", 16);
        (*client)->user = 1;
    } else
        write((*client)->ctrl_sock, "Error\r\n", 7);
}

void passwd_command(clients_t **client, char *line)
{
    if ((*client)->passwd == 1) {
        write((*client)->ctrl_sock, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if ((*client)->user == 0) {
        write((*client)->ctrl_sock, "332 Need account for login.\r\n", 29);
        return;
    }
    char *passwd = strchr(line, ' ');
    if (passwd != NULL)
        passwd++;
    else {
        write((*client)->ctrl_sock, "Error\r\n", 7);
        return;
    }
    if (strcmp(passwd, "") == 0) {
        write((*client)->ctrl_sock, "230 User logged in, proceed.\r\n", 30);
        (*client)->passwd = 1;
    } else
        write((*client)->ctrl_sock, "Error\r\n", 7);
}
