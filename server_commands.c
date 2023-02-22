/*
** EPITECH PROJECT, 2023
** server_commands.c
** File description:
** server_commands
*/

#include "server.h"

int more_commands(clients_t **client, char *buffer)
{
    if (strcmp(buffer, "NOOP") == 0) {
        write((*client)->ctrl_sock, "200 Command okay.\r\n", 20); return 1;
    }
    if (strcmp(buffer, "PWD") == 0) {
        pwd_command(client); return 1;
    }
    if (strstr(buffer, "CWD")) {
        cwd_command(client, buffer); return 1;
    }
    if (strcmp(buffer, "CDUP") == 0) {
        cdup_command(client); return 1;
    }
    if (strstr(buffer, "DELE")) {
        dele_command(client, buffer); return 1;
    }
    if (strcmp(buffer, "HELP") == 0) {
        help_command(client); return 1;
    }
    return 0;
}

int commands(clients_t **cls, clients_t **client, char *buffer)
{
    if (strcmp(buffer, "PASV") == 0) {
        passv_command(client); return 0;
    }
    if (strstr(buffer, "RETR")) {
        retr_command(client, buffer); return 0;
    }
    if (strstr(buffer, "USER")) {
        user_command(client, buffer); return 0;
    }
    if (strstr(buffer, "PASS")) {
        passwd_command(client, buffer); return 0;
    }
    if (strcmp(buffer, "QUIT") == 0) {
        quit_command(cls, client); return 1;
    }
    if (more_commands(client, buffer) == 1)
        return 0;
    write((*client)->ctrl_sock, "500 Syntax error, ", 18);
    write((*client)->ctrl_sock, "command unrecognized.\r\n", 23);
    return 0;
}

int check_commands_socket(clients_t **cls, clients_t **client)
{
    char buffer[1025]; int valread;
    if ((valread = read((*client)->ctrl_sock, buffer, 1024)) == 0) {
        remove_client(cls, (*client)->ctrl_sock); return 1;
    } else {
        buffer[valread - 2] = '\0';
        if (commands(cls, client, buffer) == 1)
            return 1;
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
            res = check_commands_socket(cl, &tmp);
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
