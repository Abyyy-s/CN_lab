/*
 * Experiment : Concurrent Date & Time Server (TCP)
 * Aim        : To implement a concurrent Time Server using TCP socket programming
 *              where the client sends a time request to the server, the server
 *              retrieves its current system time, and sends it back to the client.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define PORT 9001

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Date & Time TCP Server started on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        /* Fork for concurrent handling */
        pid_t pid = fork();
        if (pid == 0) {
            /* Child process */
            close(server_fd);

            char request[20];
            recv(new_socket, request, sizeof(request), 0);

            time_t t = time(NULL);
            char *timeStr = ctime(&t);

            printf("Request received. Sending time: %s", timeStr);
            send(new_socket, timeStr, strlen(timeStr) + 1, 0);

            close(new_socket);
            exit(0);
        } else {
            /* Parent process */
            close(new_socket);
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(server_fd);
    return 0;
}
