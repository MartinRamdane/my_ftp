/*
** EPITECH PROJECT, 2023
** server.h
** File description:
** server
*/

#ifndef SERVER
    #define SERVER

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void create_server(char *port);

#endif /* !SERVER */
