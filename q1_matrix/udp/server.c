/*
 * Experiment : UDP Client-Server - Identify Matrix Type (Upper/Lower/Diagonal)
 * Aim        : Client sends a randomly generated square matrix via UDP; server
 *              determines its type (upper triangular, lower triangular, or diagonal).
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12346

typedef struct {
    int N;
    int matrix[10][10];
} Packet;

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    Packet pkt;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP Server waiting...\n");

    recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&cliaddr, &len);

    int N = pkt.N;
    printf("\nReceived %dx%d Matrix:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d ", pkt.matrix[i][j]);
        printf("\n");
    }

    int upper = 1, lower = 1, diagonal = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > j  && pkt.matrix[i][j] != 0) upper    = 0;
            if (i < j  && pkt.matrix[i][j] != 0) lower    = 0;
            if (i != j && pkt.matrix[i][j] != 0) diagonal = 0;
        }
    }

    char result[50];
    if (diagonal)       strcpy(result, "Diagonal Matrix");
    else if (upper)     strcpy(result, "Upper Triangular Matrix");
    else if (lower)     strcpy(result, "Lower Triangular Matrix");
    else                strcpy(result, "Not a Special Matrix");

    printf("Result: %s\n", result);
    sendto(sockfd, result, strlen(result) + 1, 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
