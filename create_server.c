/*
** EPITECH PROJECT, 2023
** create_server.c
** File description:
** create_server
*/

#include "server.h"

void add_new_socket_to_array(int *client_socket, int cfd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_socket[i] == 0) {
            client_socket[i] = cfd;
            return;
        }
    }
}

void accept_socket(int m_sock, struct sockaddr_in addr, int addrl, int *cls)
{
    int cfd = accept(m_sock, (struct sockaddr*)&addr, (socklen_t*)&addrl);
    if (cfd < 0)
        exit(EXIT_FAILURE);
    char *ip = inet_ntoa(addr.sin_addr);
    int port_co = ntohs(addr.sin_port);
    printf("Connection from %s:%i\n", ip, port_co);
    write(cfd, "Hello World!!!\r\n", 16);
    add_new_socket_to_array(cls, cfd);
}

void check_closing_socket(int sd, int *cl, int i, struct sockaddr_in addr)
{
    char buffer[1025];
    int valread;
    if ((valread = read(sd, buffer, 1024)) == 0) {
        close(sd);
        cl[i] = 0;
    } else {
        buffer[valread - 2] = '\0';
        if (strcmp(buffer, "PASV") == 0)
            passv_command(sd, addr);
        if (strstr(buffer, "PORT")) {
            port_command();
        }
    }
}

void operations_on_sockets(fd_set *readfds, int *cl, struct sockaddr_in addr)
{
    int sd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        sd = cl[i];
        if (FD_ISSET(sd, readfds)) {
            check_closing_socket(sd, cl, i, addr);
        }
    }
}

void add_and_set_sockets(fd_set *readfds, int *m_sd, int m_sock, int *cl_sock)
{
    int sd;
    FD_ZERO(readfds);
    FD_SET(m_sock, readfds);
    *m_sd = m_sock;
    for (int i = 0 ; i < MAX_CLIENTS ; i++) {
        sd = cl_sock[i];
        if (sd > 0)
            FD_SET(sd, readfds);
        if (sd > *m_sd)
            *m_sd = sd;
    }
}
