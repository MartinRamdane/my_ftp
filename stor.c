/*
** EPITECH PROJECT, 2023
** stor.c
** File description:
** stor
*/

#include "server.h"

int upload_file(clients_t **client, char *path)
{
    int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        write((*client)->ctrl_sock, "550 Requested action not taken;", 31);
        write((*client)->ctrl_sock, " file unavailable...\r\n", 22);
        return 1;
    }
    char buffer[2048];
    int valread;
    while ((valread = read((*client)->data_sock, buffer, 2048)) > 0) {
        write(fd, buffer, valread);
    }
    close(fd);
    return 0;
}

void connect_to_data(clients_t **client)
{
    write((*client)->ctrl_sock, "150 File status okay;", 21);
    write((*client)->ctrl_sock, " about to open data connection.\r\n", 33);
    set_data_sock(client);
}

void stor_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *path = strchr(line, ' ');
    if (path != NULL)
        path++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    connect_to_data(client);
    if ((*client)->data_sock == 0) {
        write((*client)->ctrl_sock, "425 Can't open data connection.\r\n", 33);
        return;
    }
    if (upload_file(client, path) == 1)
        return;
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
}
