/*
 * Experiment : TCP Client-Server - Matrix Multiplication
 * Aim        : To implement a TCP client-server program where the client sends
 *              two randomly generated square matrices to the server, and the
 *              server computes their product and sends the result back.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12349

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    MatPair mp;
    int result[10][10];
    int N;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter order of matrices (N x N): ");
    scanf("%d", &mp.N);

    srand(time(0));

    printf("\nMatrix A:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.A[i][j] = rand() % 10;   /* 0 to 9 for readable products */
            printf("%4d ", mp.A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.B[i][j] = rand() % 10;
            printf("%4d ", mp.B[i][j]);
        }
        printf("\n");
    }

    /* Send both matrices to server */
    send(sock, &mp, sizeof(mp), 0);

    /* Receive result */
    recv(sock, &N, sizeof(N), 0);
    recv(sock, result, sizeof(result), 0);

    printf("\nResult (A x B) from Server:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%6d ", result[i][j]);
        printf("\n");
    }

    close(sock);
    return 0;
}
