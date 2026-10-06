/*
 * Experiment : TCP Client-Server - Odd or Even Check
 * Aim        : Client sends a number to the server; server checks if it is odd or even and returns the result.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5007

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

    printf("Odd or Even Check TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    int num;
    recv(new_socket, &num, sizeof(num), 0);
    printf("Received: %d\n", num);

    char result[100];
    snprintf(result, sizeof(result), "%d is %s.", num, (num % 2 == 0) ? "Even" : "Odd");

    send(new_socket, result, strlen(result) + 1, 0);
    printf("Result: %s\n", result);

    close(new_socket);
    close(server_fd);
    return 0;
}
