/*
 * Experiment : Concurrent Date & Time Client (TCP)
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9001

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /* Send request */
    char req[] = "TIME_REQUEST";
    send(sock, req, strlen(req), 0);

    /* Receive time */
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server Date & Time: %s\n", buffer);

    close(sock);
    return 0;
}
