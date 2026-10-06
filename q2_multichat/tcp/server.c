/*
 * Experiment : Multi-user Chat Server using TCP and select()
 * Aim        : To implement a multi-user chat server using TCP socket programming
 *              where multiple clients communicate simultaneously through a central
 *              server using the select() system call.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT      8888
#define MAX_CLIENTS 10
#define BUFFER    1024

int main() {
    int server_fd, new_socket, client_sockets[MAX_CLIENTS];
    int max_sd, sd, activity;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER];
    fd_set readfds;

    /* Initialise all client sockets to 0 */
    for (int i = 0; i < MAX_CLIENTS; i++)
        client_sockets[i] = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Multi-user Chat Server started on port %d\n", PORT);
    printf("Waiting for clients...\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        /* New incoming connection */
        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            printf("New client connected: socket fd %d, IP %s, Port %d\n",
                   new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            char welcome[] = "Welcome to the chat! Type your message.\n";
            send(new_socket, welcome, strlen(welcome), 0);

            /* Add to client list */
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    break;
                }
            }
        }

        /* Data from a client */
        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, BUFFER - 1);
                if (valread == 0) {
                    /* Client disconnected */
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Client disconnected: IP %s, Port %d\n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    printf("Client %d: %s", sd, buffer);

                    /* Broadcast to all other clients */
                    char broadcast[BUFFER + 20];
                    snprintf(broadcast, sizeof(broadcast), "Client %d: %s", sd, buffer);
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        int dest = client_sockets[j];
                        if (dest != 0 && dest != sd)
                            send(dest, broadcast, strlen(broadcast), 0);
                    }
                }
            }
        }
    }
    return 0;
}
