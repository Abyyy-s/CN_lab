/*
 * Experiment : Multi-user Chat Client (TCP)
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT   8888
#define BUFFER 1024

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER];
    fd_set readfds;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to chat server. Type messages below:\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sock, &readfds);

        select(sock + 1, &readfds, NULL, NULL, NULL);

        /* Message from server */
        if (FD_ISSET(sock, &readfds)) {
            int n = read(sock, buffer, BUFFER - 1);
            if (n <= 0) {
                printf("Server disconnected.\n");
                break;
            }
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        /* User input */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buffer, BUFFER, stdin);
            send(sock, buffer, strlen(buffer), 0);
        }
    }

    close(sock);
    return 0;
}
