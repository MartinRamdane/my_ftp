/*
** EPITECH PROJECT, 2023
** retr.c
** File description:
** retr
*/

#include "server.h"

char *get_file(clients_t **client, char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        write((*client)->ctrl_sock, "550 Requested action not taken;", 31);
        write((*client)->ctrl_sock, " file unavailable...\r\n", 22);
        return NULL;
    }
    struct stat s;
    stat(path, &s);
    char *buffer = malloc(sizeof(char) * (s.st_size + 1));
    read(fd, buffer, s.st_size);
    close(fd);
    return buffer;
}

void print_msg(clients_t **client, char *file)
{
    write((*client)->ctrl_sock, "150 File status okay;", 21);
    write((*client)->ctrl_sock, " about to open data connection.\r\n", 33);
    if ((*client)->to_connect) {
        connect((*client)->data_sock, (struct sockaddr *)&(*client)->addr_data
        , sizeof((*client)->addr_data));
        (*client)->to_connect = 0;
    }
    if ((*client)->data_sock == 0) {
        write((*client)->ctrl_sock, "425 Can't open data connection.\r\n", 33);
        return;
    }
    write((*client)->data_sock, file, strlen(file));
    free(file);
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
}

void retr_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *path = strchr(line, ' ');
    if (path != NULL)
        path++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return;
    }
    char *file = get_file(client, path);
    if (!file) {
        write((*client)->ctrl_sock, "550 Requested action not taken;", 31);
        write((*client)->ctrl_sock, " file unavailable...\r\n", 22); return;
    }
    print_msg(client, file);
}
