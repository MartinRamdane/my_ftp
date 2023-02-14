/*
** EPITECH PROJECT, 2023
** create_server.c
** File description:
** create_server
*/

#include "server.h"

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
        do_operations_on_other_sockets(&readfds, client_socket);
    }
    close(master_socket);
}
