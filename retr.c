/*
** EPITECH PROJECT, 2023
** retr.c
** File description:
** retr
*/

#include "server.h"

char *get_file(char *path)
{
    printf("path: %s\n", path);
    int fd = open(path, O_RDONLY);
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
    if ((*client)->data_sock == 0) {
        write((*client)->ctrl_sock, "Error\r\n", 7); return;
    }
    write((*client)->data_sock, file, strlen(file));
    write((*client)->data_sock, "\r\n", 2); free(file);
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
    write((*client)->ctrl_sock, "Requested file action successful\r\n", 34);
}

void retr_command(clients_t **client, char *line)
{
    char *path = strchr(line, ' ');
    if (path != NULL)
        path++;
    else {
        write((*client)->ctrl_sock, "Error\r\n", 7); return;
    }
    int len = strlen((*client)->dir) + strlen(path);
    len += (path[0] != '/' ? 1 : 0);
    char *path_dir = malloc(sizeof(char) * (len + 1));
    strcpy(path_dir, (*client)->dir);
    if (path[0] != '/')
        path_dir = strcat(path_dir, "/");
    path_dir = strcat(path_dir, path); char *file = get_file(path_dir);
    if (!file) {
        write((*client)->ctrl_sock, "Error\r\n", 7); return;
    }
    print_msg(client, file);
    free(path_dir);
}
