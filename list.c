/*
** EPITECH PROJECT, 2023
** list.c
** File description:
** list
*/

#include "server.h"

void list_in_dir(clients_t **client, char *path)
{
    DIR *fd;
    struct dirent *dir;
    fd = opendir(path);
    if (fd) {
        while ((dir = readdir(fd)) != NULL) {
            write((*client)->ctrl_sock, dir->d_name, strlen(dir->d_name));
            write((*client)->ctrl_sock, "\r\n", 2);
        }
        closedir(fd);
    } else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
    }
}

void list_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    write((*client)->ctrl_sock, "150 File status okay;", 21);
    write((*client)->ctrl_sock, " about to open data connection.\r\n", 33);
    if (strcmp(line, "LIST") == 0) {
        list_in_dir(client, ".");
    } else {
        char *dir = strchr(line, ' ');
        if (dir != NULL)
            dir++;
        else {
            write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
            write((*client)->ctrl_sock, "or argument.\r\n", 14);
            return;
        }
        list_in_dir(client, dir);
    }
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
}
