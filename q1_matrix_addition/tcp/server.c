/*
 * Experiment : TCP Client-Server - Matrix Addition
 * Aim        : Client sends two matrices; server computes their sum and returns it.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12347

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    MatPair mp;
    int result[10][10];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Matrix Addition TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    recv(new_socket, &mp, sizeof(mp), 0);

    int N = mp.N;
    printf("\nMatrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.A[i][j]);
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.B[i][j]);
        printf("\n");
    }

    /* Compute A + B */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = mp.A[i][j] + mp.B[i][j];

    printf("\nResult (A + B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", result[i][j]);
        printf("\n");
    }

    /* Send back N and result */
    send(new_socket, &N, sizeof(N), 0);
    send(new_socket, result, sizeof(result), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
