/*
 * Experiment : TCP Client-Server - Factorial
 * Aim        : Client sends a number N to the server; server computes N! and returns the result.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5015

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
    listen(server_fd, 3);

    printf("Factorial TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    int N;
    recv(new_socket, &N, sizeof(N), 0);
    printf("Received: %d\n", N);

    long long fact = 1;
    for (int i = 2; i <= N; i++) fact *= i;
    printf("%d! = %lld\n", N, fact);

    send(new_socket, &fact, sizeof(fact), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
