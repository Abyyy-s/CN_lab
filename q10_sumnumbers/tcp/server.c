/*
 * Experiment : TCP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5011

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

    printf("Sum of N Numbers TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    int N;
    recv(new_socket, &N, sizeof(N), 0);
    float nums[100];
    recv(new_socket, nums, N * sizeof(float), 0);
    printf("N = %d\nNumbers: ", N);
    for (int i = 0; i < N; i++) printf("%.2f ", nums[i]);
    printf("\n");

    float sum = 0;
    for (int i = 0; i < N; i++) sum += nums[i];
    printf("Sum: %.2f\n", sum);

    send(new_socket, &sum, sizeof(sum), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
