/*
** EPITECH PROJECT, 2023
** stor.c
** File description:
** stor
*/

#include "server.h"

void upload_file(clients_t **client, char *path)
{
    FILE *fp = fopen (path, "w");
    char buffer[2048];
    read((*client)->data_sock, buffer, 2048);
    fputs(buffer, fp);
    fclose(fp);
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
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return;
    }
    write((*client)->ctrl_sock, "150 File status okay;", 21);
    write((*client)->ctrl_sock, " about to open data connection.\r\n", 33);
    if ((*client)->data_sock == 0) {
        write((*client)->ctrl_sock, "425 Can't open data connection.\r\n", 33);
        return;
    }
    upload_file(client, path);
    close((*client)->data_sock);
    write((*client)->ctrl_sock, "226 Closing data connection.\r\n", 30);
}
