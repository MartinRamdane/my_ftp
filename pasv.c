/*
** EPITECH PROJECT, 2023
** pasv.c
** File description:
** PASV command
*/

#include "server.h"

void pasv_reply_code(clients_t *client, int port, char *ip)
{
    int port1 = port / 256, port2 = port % 256;
    write(client->ctrl_sock, "227 Entering Passive Mode (", 27);
    char *token = strtok(ip, ".");
    while (token != NULL) {
        write(client->ctrl_sock, token, strlen(token));
        write(client->ctrl_sock, ",", 1);
        token = strtok(NULL, ".");
    }
    char int_str[5];
    sprintf(int_str, "%d", port1);
    write(client->ctrl_sock, int_str, strlen(int_str));
    write(client->ctrl_sock, ",", 1);
    sprintf(int_str, "%d", port2);
    write(client->ctrl_sock, int_str, strlen(int_str));
    write(client->ctrl_sock, ")\r\n", 3);
}

void accept_data_socket(clients_t **client, struct sockaddr_in addr)
{
    (*client)->addr_data = addr;
    (*client)->to_accept = 1;
}

void passv_command(clients_t **client)
{
    if ((*client)->passwd != 1) {
        write((*client)->ctrl_sock, "530 Not logged in.\r\n", 20); return;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    char *ip = inet_ntoa((*client)->addr.sin_addr);
    inet_aton(ip, &addr.sin_addr);
    addr.sin_port = htons(0);
    (*client)->data_sock = socket(AF_INET, SOCK_STREAM, 0);
    bind((*client)->data_sock, (struct sockaddr *)&addr, sizeof(addr));
    int len = sizeof(addr); struct sockaddr *tmp = (struct sockaddr *)&addr;
    getsockname((*client)->data_sock, tmp, (socklen_t*)&len);
    int port = ntohs(addr.sin_port);
    pasv_reply_code((*client), port, ip);
    listen((*client)->data_sock, 1);
    accept_data_socket(client, addr);
}
