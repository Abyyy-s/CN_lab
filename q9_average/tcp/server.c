/*
 * Experiment : TCP Client-Server - Average of Three Numbers
 * Aim        : Client sends three numbers to the server; server computes their average and returns it.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5009

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

    printf("Average of Three Numbers TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    float nums[3];
    recv(new_socket, nums, sizeof(nums), 0);
    printf("Received: %.2f, %.2f, %.2f\n", nums[0], nums[1], nums[2]);

    float avg = (nums[0] + nums[1] + nums[2]) / 3.0;
    printf("Average: %.2f\n", avg);

    send(new_socket, &avg, sizeof(avg), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
