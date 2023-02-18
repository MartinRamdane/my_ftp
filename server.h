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
#include <signal.h>

#define MAX_CLIENTS 100

typedef struct clients {
    int ctrl_sock;
    int data_sock;
    struct sockaddr_in addr;
    struct clients *next;
} clients_t;

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int rl, clients_t **cl);
void operations_on_sockets(fd_set *fd, clients_t **cl);
void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock, clients_t *cls);
void port_command(void);
void passv_command(clients_t **client);
