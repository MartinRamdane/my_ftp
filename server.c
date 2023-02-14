/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include "server.h"

void add_new_socket_to_array(int *client_socket, int cfd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_socket[i] == 0) {
            client_socket[i] = cfd;
            // printf("Adding to list of sockets as %d\n" , i);
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

void check_closing_socket(int sd, int *client_socket, int i)
{
    char buffer[1025];
    int valread;
    if ((valread = read(sd, buffer, 1024)) == 0) {
        // getpeername(sd, (struct sockaddr*)&myaddr, (socklen_t*)&addrlen);
        // printf("Host disconnected, ip %s, port %d \n", inet_ntoa(myaddr.sin_addr), ntohs(myaddr.sin_port));
        // printf("host disconected\n");
        close(sd);
        client_socket[i] = 0;
    } else {
        buffer[valread] = '\0';
        write(sd, buffer, strlen(buffer));
    }
}

void do_operations_on_other_sockets(fd_set *readfds, int *client_socket)
{
    int sd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        sd = client_socket[i];
        if (FD_ISSET(sd, readfds)) {
            check_closing_socket(sd, client_socket, i);
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
