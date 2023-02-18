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
        new_client->ctrl_sock = cfd;
        new_client->data_sock = 0;
        new_client->addr = addr;
        new_client->next = NULL;
        (*cls) = new_client;
    } else {
        clients_t *tmp = (*cls);
        while (tmp->next != NULL)
            tmp = tmp->next;
        clients_t *new_client = malloc(sizeof(clients_t));
        new_client->ctrl_sock = cfd;
        new_client->data_sock = 0;
        new_client->addr = addr;
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
    add_new_socket_to_array(cl, cfd, addr);
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
        if (curr->ctrl_sock == value) {
            clear_cl(&prev, cls, &curr);
            close(curr->ctrl_sock);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

int check_closing_socket(clients_t **cls, clients_t **client)
{
    char buffer[1025];
    int valread;
    if ((valread = read((*client)->ctrl_sock, buffer, 1024)) == 0) {
        remove_client(cls, (*client)->ctrl_sock);
        return 1;
    } else {
        buffer[valread - 2] = '\0';
        if (strcmp(buffer, "PASV") == 0)
            passv_command(client);
        if (strstr(buffer, "RETR"))
            retr_command(client, buffer);
    }
    return 0;
}

void operations_on_sockets(fd_set *fd, clients_t **cl)
{
    clients_t *tmp = *cl;
    clients_t *prev = NULL;
    int res = 0;
    while (tmp != NULL) {
        if (FD_ISSET(tmp->ctrl_sock, fd))
            res = check_closing_socket(cl, &tmp);
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
        sd = tmp->ctrl_sock;
        if (sd > 0)
            FD_SET(sd, fd);
        if (sd > *m_sd)
            *m_sd = sd;
        tmp = tmp->next;
    }
}
