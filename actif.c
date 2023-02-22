/*
** EPITECH PROJECT, 2023
** actif.c
** File description:
** actif
*/

#include "server.h"

// void pasv_reply_code(clients_t *client, int port, char *ip)
// {
//     int port1 = port / 256, port2 = port % 256;
//     write(client->ctrl_sock, "227 Entering Passive Mode (", 27);
//     char *token = strtok(ip, ".");
//     while (token != NULL) {
//         write(client->ctrl_sock, token, strlen(token));
//         write(client->ctrl_sock, ",", 1);
//         token = strtok(NULL, ".");
//     }
//     char int_str[5];
//     sprintf(int_str, "%d", port1);
//     write(client->ctrl_sock, int_str, strlen(int_str));
//     write(client->ctrl_sock, ",", 1);
//     sprintf(int_str, "%d", port2);
//     write(client->ctrl_sock, int_str, strlen(int_str));
//     write(client->ctrl_sock, ")\r\n", 3);
// }

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
        write((*client)->ctrl_sock, "or argument.\r\n", 14); return;
    }
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
