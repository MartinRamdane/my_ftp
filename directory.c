/*
** EPITECH PROJECT, 2023
** directory.c
** File description:
** directory
*/

#include "server.h"

void pwd_command(clients_t **client)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        write((*client)->ctrl_sock, "257 \"", 6);
        write((*client)->ctrl_sock, cwd, strlen(cwd));
        write((*client)->ctrl_sock, "\" created.\r\n", 12);
    } else
        write((*client)->ctrl_sock, "Error\r\n", 7);
}

void cwd_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *dir = strchr(line, ' ');
    if (dir != NULL)
        dir++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return;
    }
    if (chdir(dir) == 0) {
        write((*client)->ctrl_sock, "250 Requested file action okay, ", 32);
        write((*client)->ctrl_sock, "completed.\r\n", 12);
    } else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
    }
}

void cdup_command(clients_t **client)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        chdir("../");
        write((*client)->ctrl_sock, "200 Command okay.\r\n", 19);
    } else
        write((*client)->ctrl_sock, "Error\r\n", 7);
}

void dele_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *file = strchr(line, ' ');
    if (file != NULL)
        file++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return;
    }
    if (remove(file) == 0) {
        write((*client)->ctrl_sock, "250 Requested file action okay, ", 32);
        write((*client)->ctrl_sock, "completed.\r\n", 12);
    } else {
        write((*client)->ctrl_sock, "550 Requested action not taken;", 31);
        write((*client)->ctrl_sock, " file unavailable...\r\n", 22);
    }
}
