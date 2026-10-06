/*
 * Experiment : TCP Client-Server - Prime or Composite Check
 * Aim        : Client sends a number to the server; server checks if it is prime or composite and returns the result.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5005

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

    printf("Prime or Composite Check TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    int num;
    recv(new_socket, &num, sizeof(num), 0);
    printf("Received: %d\n", num);

    char result[100];
    if (num < 2) {
        snprintf(result, sizeof(result), "%d is neither prime nor composite.", num);
    } else {
        int isPrime = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) { isPrime = 0; break; }
        }
        snprintf(result, sizeof(result), "%d is %s.", num, isPrime ? "Prime" : "Composite");
    }

    send(new_socket, result, strlen(result) + 1, 0);
    printf("Result: %s\n", result);

    close(new_socket);
    close(server_fd);
    return 0;
}
