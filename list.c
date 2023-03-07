/*
** EPITECH PROJECT, 2023
** list.c
** File description:
** list
*/

#include "server.h"

int print_msg_file(clients_t **client)
{
    write((*client)->ctrl_sock, "150 File status okay;", 21);
    write((*client)->ctrl_sock, " about to open data connection.\r\n", 33);
    if (set_data_sock(client) == 1)
        return 1;
    return 0;
}

int list_in_dir(clients_t **client, char *path)
{
    DIR *fd;
    struct dirent *dir;
    fd = opendir(path);
    if (fd) {
        if (print_msg_file(client) == 1) return 1;
        if ((*client)->data_sock == 0) {
            write((*client)->ctrl_sock, "425 Can't open data connection.\r\n"
            , 33); return 1;
        }
        while ((dir = readdir(fd)) != NULL) {
            write((*client)->data_sock, dir->d_name, strlen(dir->d_name));
            write((*client)->data_sock, "\r\n", 2);
        }
        closedir(fd);
    } else {
        write((*client)->ctrl_sock, "450 Requested file action not ", 30);
        write((*client)->ctrl_sock, "taken.\r\n", 8);
        return 1;
    }
    return 0;
}

void close_co(clients_t **client)
{
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
}

int check_co(clients_t **client)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20);
        return 1;
    }
    return 0;
}

void list_command(clients_t **client, char *line)
{
    int res = 0;
    if (check_co(client) == 1)
        return;
    if (strcmp(line, "LIST") == 0) {
        res = list_in_dir(client, ".");
    } else {
        char *dir = strchr(line, ' ');
        if (dir != NULL)
            dir++;
        else {
            write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
            write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
        }
        res = list_in_dir(client, dir);
    }
    if (res == 0)
        close_co(client);
}
