/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include "server.h"

void create_server(char *port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr;
    int addrlen = sizeof(myaddr);
    myaddr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    bind(sfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
    listen(sfd, 100);
    while (1) {
        int cfd = accept(sfd, (struct sockaddr*)&myaddr, (socklen_t*)&addrlen);
        if (cfd < 0)
            exit(EXIT_FAILURE);
        if (fork() == 0) {
            char *ip = inet_ntoa(myaddr.sin_addr);
            int port_co = ntohs(myaddr.sin_port);
            printf("Connection from %s:%i\n", ip, port_co);
            write(cfd, "Hello World!!!\r\n", 16);
            close(cfd);
        } else
            close(cfd);
    }
    close(sfd);
}