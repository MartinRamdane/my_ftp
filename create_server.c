/*
** EPITECH PROJECT, 2023
** create_server.c
** File description:
** create_server
*/

#include "server.h"

void add_new_socket_to_array(clients_t **cls, int cfd)
{
    if ((*cls) == NULL) {
        clients_t *new_client = malloc(sizeof(clients_t));
        new_client->socket = cfd;
        new_client->next = NULL;
        (*cls) = new_client;
    } else {
        clients_t *tmp = (*cls);
        while (tmp->next != NULL)
            tmp = tmp->next;
        clients_t *new_client = malloc(sizeof(clients_t));
        new_client->socket = cfd;
        new_client->next = NULL;
        tmp->next = new_client;
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
    write(cfd, "Hello World!!!\r\n", 16);
    add_new_socket_to_array(cl, cfd);
}

static void clear_cl(clients_t **prev, clients_t **cls, clients_t **curr)
{
    if (*prev == NULL) {
        *cls = (*curr)->next;
    } else {
        (*prev)->next = (*curr)->next;
    }
}

static void remove_client(clients_t **cls, int value)
{
    clients_t *prev = NULL;
    clients_t *curr = *cls;
    while (curr != NULL) {
        if (curr->socket == value) {
            clear_cl(&prev, cls, &curr);
            close(curr->socket);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

int check_closing_socket(clients_t **cls, int socket, struct sockaddr_in addr)
{
    char buffer[1025];
    int valread;
    if ((valread = read(socket, buffer, 1024)) == 0) {
        remove_client(cls, socket);
        return 1;
    } else {
        buffer[valread - 2] = '\0';
        if (strcmp(buffer, "PASV") == 0)
            passv_command(socket, addr);
        if (strstr(buffer, "PORT")) {
            port_command();
        }
    }
    return 0;
}

void operations_on_sockets(fd_set *fd, clients_t **cl, struct sockaddr_in adr)
{
    clients_t *tmp = *cl;
    clients_t *prev = NULL;
    int res = 0;
    while (tmp != NULL) {
        if (FD_ISSET(tmp->socket, fd))
            res = check_closing_socket(cl, tmp->socket, adr);
        if (res == 1) {
            tmp = *cl; res = 0; continue;
        }
        prev = tmp;
        tmp = tmp->next;
        if (prev != NULL && prev->next == NULL) {
            break;
        }
    }
}

void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock, clients_t *cls)
{
    int sd;
    FD_ZERO(fd);
    FD_SET(m_sock, fd);
    *m_sd = m_sock;
    clients_t *tmp = cls;
    while (tmp != NULL) {
        sd = tmp->socket;
        if (sd > 0)
            FD_SET(sd, fd);
        if (sd > *m_sd)
            *m_sd = sd;
        tmp = tmp->next;
    }
}
