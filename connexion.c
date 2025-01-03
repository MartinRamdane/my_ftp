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
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return;
    }
    write((*client)->ctrl_sock, "331 User name okay, ", 20);
    write((*client)->ctrl_sock, "need password.\r\n", 16);
    (*client)->user = strdup(username);
}

int check_login(clients_t **client)
{
    if (strcmp((*client)->user, "Anonymous") == 0)
        return 1;
    return 0;
}

void passwd_command(clients_t **client, char *line)
{
    if ((*client)->passwd == 1) {
        write((*client)->ctrl_sock, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if ((*client)->user == NULL) {
        write((*client)->ctrl_sock, "332 Need account for login.\r\n", 29);
        return;
    }
    char *passwd = strchr(line, ' ');
    if (passwd != NULL)
        passwd++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    if (strcmp(passwd, "") == 0 && check_login(client) == 1) {
        write((*client)->ctrl_sock, "230 User logged in, proceed.\r\n", 30);
        (*client)->passwd = 1;
    } else
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20);
}

void quit_command(clients_t **cls, clients_t **client)
{
    write((*client)->ctrl_sock, "221 Service closing control ", 29);
    write((*client)->ctrl_sock, "connection.\r\n", 13);
    remove_client(cls, (*client)->ctrl_sock);
}
