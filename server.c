/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include "server.h"

void passv_command(int sd, struct sockaddr_in addr)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    char *ip = inet_ntoa(addr.sin_addr);
    inet_aton(ip, &myaddr.sin_addr);
    int port1 = 20, port2 = 235;
    int port = (port1 * 256) + port2;
    myaddr.sin_port = htons(port);
    bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    write(sd, "227 Entering Passive Mode (", 27);
    char *token = strtok(ip, ".");
    while (token != NULL) {
        write(sd, token, strlen(token));
        write(sd, ",", 1);
        token = strtok(NULL, ".");
    }
    char int_str[5]; sprintf(int_str, "%d", port1);
    write(sd, int_str, strlen(int_str)); write(sd, ",", 1);
    sprintf(int_str, "%d", port2); write(sd, int_str, strlen(int_str));
    write(sd, ")\r\n", 3);
}

void port_command(void)
{
    ;
}

void create_server(char *port)
{
    int client_socket[MAX_CLIENTS], max_sd;
    for (int i = 0; i < MAX_CLIENTS; i++)
        client_socket[i] = 0;
    fd_set readfds; int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr; int addrlen = sizeof(myaddr);
    myaddr.sin_family = AF_INET; inet_aton("127.0.0.1", &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    bind(master_socket, (struct sockaddr *)&myaddr, sizeof(myaddr));
    listen(master_socket, MAX_CLIENTS);
    while (1) {
        add_and_set_sockets(&readfds, &max_sd, master_socket, client_socket);
        int ret_val = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (ret_val <= 0)
            perror("select()");
        if (FD_ISSET(master_socket, &readfds))
            accept_socket(master_socket, myaddr, addrlen, client_socket);
        operations_on_sockets(&readfds, client_socket, myaddr);
    }
    close(master_socket);
}
