/*
** EPITECH PROJECT, 2023
** actif.c
** File description:
** actif
*/

#include "server.h"

void create_sock(clients_t **client, char *ip, int port)
{
    (*client)->data_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    inet_addr(ip);
    client_addr.sin_port = htons(port);
    connect((*client)->data_sock, (struct sockaddr *)&client_addr
    , sizeof(client_addr));
    write((*client)->ctrl_sock, "200 Command okay.\r\n", 19);
}

int get_port(clients_t **client)
{
    char *token = strtok(NULL, ",");
    char *port1 = strdup(token);
    if ((token = strtok(NULL, ",")) == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return (-1);
    }
    char *port2 = strdup(token);
    return ((atoi(port1) * 256) + atoi(port2));
}

char *get_ip(clients_t **client, char *line)
{
    char *token = strtok(line, ","), *ip = strdup(token);
    if ((token = strtok(NULL, ",")) == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return NULL;
    }
    strcat(ip, "."); strcat(ip, token);
    if ((token = strtok(NULL, ",")) == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return NULL;
    }
    strcat(ip, "."); strcat(ip, token);
    if ((token = strtok(NULL, ",")) == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14);
        return NULL;
    }
    strcat(ip, "."); strcat(ip, token);
    return ip;
}

void port_command(clients_t **client, char *line)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    char *infos = strchr(line, ' ');
    if (infos != NULL)
        infos++;
    else {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    char *ip = get_ip(client, infos);
    if (ip == NULL) {
        write((*client)->ctrl_sock, "501 Syntax error in parameters ", 31);
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
    int port = get_port(client);
    if (port == -1)
        return;
    create_sock(client, ip, port);
}
