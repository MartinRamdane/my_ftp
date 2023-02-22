/*
** EPITECH PROJECT, 2023
** actif.c
** File description:
** actif
*/

#include "server.h"

void create_sock(clients_t **client, char *ip, char *port)
{
    (*client)->data_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    inet_addr(ip);
    client_addr.sin_port = htons(atoi(port));
    connect((*client)->data_sock, (struct sockaddr *)&client_addr
    , sizeof(client_addr));
    write((*client)->ctrl_sock, "200 Command okay.\r\n", 19);
}

char *get_port(clients_t **client, char *copy)
{
    char *port = strchr(copy, '-');
    if (port != NULL)
        port++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return NULL;
    }
    return port;
}

void port_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *copy = strdup(line); char *infos = strchr(line, ' ');
    if (infos != NULL)
        infos++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    char *ip = strtok(infos, "-");
    if (ip == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    char *port = get_port(client, copy);
    if (port == NULL)
        return;
    create_sock(client, ip, port);
}
