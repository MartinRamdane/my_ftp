/*
** EPITECH PROJECT, 2023
** client.h
** File description:
** client
*/

#ifndef CLIENt
    #define CLIENT

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void create_client(char *ip, char *port);

#endif /* !CLIENT */