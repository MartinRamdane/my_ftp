/*
** EPITECH PROJECT, 2023
** server.h
** File description:
** server
*/

#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTS 100

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int addrl, int *cls);
void operations_on_sockets(fd_set *readfds, int *cl, struct sockaddr_in addr);
void add_and_set_sockets(fd_set *readfds, int *m_sd, int m_sock, int *cl_sock);
void passv_command(int sd, struct sockaddr_in addr);
void port_command(void);
