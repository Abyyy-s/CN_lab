/*
 * Experiment : UDP Client-Server - Matrix Multiplication
 * Aim        : To implement a UDP client-server program where the client sends
 *              two randomly generated square matrices to the server, and the
 *              server computes their product and sends the result back.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12350

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

typedef struct {
    int N;
    int R[10][10];
} MatResult;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    MatPair mp;
    MatResult mr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

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
    sendto(sockfd, &mp, sizeof(mp), 0, (struct sockaddr *)&servaddr, len);

    /* Receive result */
    recvfrom(sockfd, &mr, sizeof(mr), 0, (struct sockaddr *)&servaddr, &len);

    printf("\nResult (A x B) from Server:\n");
    for (int i = 0; i < mr.N; i++) {
        for (int j = 0; j < mr.N; j++)
            printf("%6d ", mr.R[i][j]);
        printf("\n");
    }

    close(sockfd);
    return 0;
}
