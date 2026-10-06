/*
 * Experiment : UDP Client-Server - Matrix Addition
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12348

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
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    MatPair mp;
    MatResult mr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Matrix Addition UDP Server waiting...\n");

    recvfrom(sockfd, &mp, sizeof(mp), 0, (struct sockaddr *)&cliaddr, &len);

    int N = mp.N;
    mr.N = N;
    printf("\nReceived Matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.A[i][j]);
        printf("\n");
    }
    printf("\nReceived Matrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.B[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mr.R[i][j] = mp.A[i][j] + mp.B[i][j];

    printf("\nResult (A + B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mr.R[i][j]);
        printf("\n");
    }

    sendto(sockfd, &mr, sizeof(mr), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
