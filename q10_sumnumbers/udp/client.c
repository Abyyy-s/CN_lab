/*
 * Experiment : UDP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5012

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    typedef struct { int N; float nums[100]; } NumPkt;
    NumPkt pkt;
    printf("How many numbers? ");
    scanf("%d", &pkt.N);
    printf("Enter %d numbers: ", pkt.N);
    for (int i = 0; i < pkt.N; i++) scanf("%f", &pkt.nums[i]);
    sendto(sockfd, &pkt, sizeof(int) + pkt.N * sizeof(float), 0, (struct sockaddr *)&servaddr, len);

    float sum;
    recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&servaddr, &len);
    printf("Sum from Server: %.2f\n", sum);

    close(sockfd);
    return 0;
}
