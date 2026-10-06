/*
 * Experiment : TCP Client-Server - Palindrome Check
 * Aim        : Client sends a string or number to the server; server checks if it is a palindrome and returns the result.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5003

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

    printf("Palindrome Check TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    char str[256];
    recv(new_socket, str, sizeof(str), 0);
    printf("Received: %s\n", str);

    int n = strlen(str);
    int isPalin = 1;
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - 1 - i]) { isPalin = 0; break; }
    }
    char result[100];
    snprintf(result, sizeof(result), "\"%s\" is %s a palindrome.", str, isPalin ? "" : "NOT");

    send(new_socket, result, strlen(result) + 1, 0);
    printf("Result: %s\n", result);

    close(new_socket);
    close(server_fd);
    return 0;
}
