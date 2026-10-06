/*
 * Experiment : UDP Client-Server - Identify Matrix Type (Upper/Lower/Diagonal)
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

#define PORT 12346

typedef struct {
    int N;
    int matrix[10][10];
} Packet;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    Packet pkt;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter order of matrix (N): ");
    scanf("%d", &pkt.N);

    srand(time(0));
    printf("\nGenerated Matrix:\n");
    for (int i = 0; i < pkt.N; i++) {
        for (int j = 0; j < pkt.N; j++) {
            pkt.matrix[i][j] = rand() % 51;
            printf("%3d ", pkt.matrix[i][j]);
        }
        printf("\n");
    }

    sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&servaddr, len);

    char result[50];
    recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&servaddr, &len);
    printf("\nMatrix Type: %s\n", result);

    close(sockfd);
    return 0;
}
