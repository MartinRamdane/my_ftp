/*
** EPITECH PROJECT, 2023
** server.h
** File description:
** server
*/

#ifndef SERVER
    #define SERVER

#define MAX_CLIENTS 100

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int addrl, int *cls);
void do_operations_on_other_sockets(fd_set *readfds, int *client_socket);
void add_and_set_sockets(fd_set *readfds, int *m_sd, int m_sock, int *cl_sock);

#endif /* !SERVER */
