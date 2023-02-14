/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

void create_client(char *ip, char *port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    inet_addr(ip);
    client_addr.sin_port = htons(atoi(port));
    connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    char buffer[1024];
    if (read(sockfd, buffer, 1024) > 0)
        printf("Server said: %s", buffer);
    close(sockfd);
}
