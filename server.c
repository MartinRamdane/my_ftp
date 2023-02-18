/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include "server.h"

static void free_all_clients(clients_t *clients)
{
    while (clients != NULL) {
        clients_t *tmp = clients->next;
        close(clients->ctrl_sock);
        free(clients);
        clients = tmp;
    }
}

void create_server(char *port)
{
    clients_t *clients = malloc(sizeof(clients_t));
    clients = NULL;
    int max_sd;
    fd_set readfds; int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr; int addrlen = sizeof(myaddr);
    myaddr.sin_family = AF_INET; inet_aton("0.0.0.0", &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    bind(master_socket, (struct sockaddr *)&myaddr, sizeof(myaddr));
    listen(master_socket, MAX_CLIENTS);
    while (1) {
        add_and_set_sockets(&readfds, &max_sd, master_socket, clients);
        int ret_val = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (ret_val <= 0)
            perror("select()");
        if (FD_ISSET(master_socket, &readfds))
            accept_socket(master_socket, myaddr, addrlen, &clients);
        operations_on_sockets(&readfds, &clients);
    }
    close(master_socket);
    free_all_clients(clients);
}
