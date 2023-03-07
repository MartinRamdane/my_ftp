/*
** EPITECH PROJECT, 2023
** create_server.c
** File description:
** create_server
*/

#include "server.h"

void add_new_socket_to_array(clients_t **cls, int cfd, struct sockaddr_in addr)
{
    if ((*cls) == NULL) {
        clients_t *new_client = malloc(sizeof(clients_t));
        new_client->ctrl_sock = cfd; new_client->to_connect = 0;
        new_client->data_sock = 0; new_client->user = NULL;
        new_client->passwd = 0; new_client->addr = addr;
        new_client->buffer = malloc(sizeof(char) * 1025);
        memset(new_client->buffer, 0, 1024); new_client->next = NULL;
        new_client->to_accept = 0; (*cls) = new_client;
    } else {
        clients_t *tmp = (*cls);
        while (tmp->next != NULL)
            tmp = tmp->next;
        clients_t *new_client = malloc(sizeof(clients_t));
        new_client->ctrl_sock = cfd; new_client->to_connect = 0;
        new_client->data_sock = 0; new_client->user = NULL;
        new_client->passwd = 0; new_client->addr = addr;
        new_client->buffer = malloc(sizeof(char) * 1025);
        memset(new_client->buffer, 0, 1024); new_client->next = NULL;
        new_client->to_accept = 0; tmp->next = new_client;
    }
}

void accept_socket(int m_sock, struct sockaddr_in addr, int rl, clients_t **cl)
{
    int cfd = accept(m_sock, (struct sockaddr*)&addr, (socklen_t*)&rl);
    if (cfd < 0)
        exit(EXIT_FAILURE);
    char *ip = inet_ntoa(addr.sin_addr);
    int port_co = ntohs(addr.sin_port);
    printf("Connection from %s:%i\n", ip, port_co);
    write(cfd, "220 Service ready for new user.\r\n", 33);
    add_new_socket_to_array(cl, cfd, addr);
}

void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock, clients_t *cls)
{
    int sd;
    FD_ZERO(fd);
    FD_SET(m_sock, fd);
    *m_sd = m_sock;
    clients_t *tmp = cls;
    while (tmp != NULL) {
        sd = tmp->ctrl_sock;
        if (sd > 0)
            FD_SET(sd, fd);
        if (sd > *m_sd)
            *m_sd = sd;
        tmp = tmp->next;
    }
}
