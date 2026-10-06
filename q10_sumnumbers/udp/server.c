/*
 * Experiment : UDP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5012

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Sum of N Numbers UDP Server waiting...\n");

    typedef struct { int N; float nums[100]; } NumPkt;
    NumPkt pkt;
    recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&cliaddr, &len);
    int N = pkt.N;
    printf("N = %d\nNumbers: ", N);
    for (int i = 0; i < N; i++) printf("%.2f ", pkt.nums[i]);
    printf("\n");

    float sum = 0;
    for (int i = 0; i < N; i++) sum += pkt.nums[i];
    printf("Sum: %.2f\n", sum);

    sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
