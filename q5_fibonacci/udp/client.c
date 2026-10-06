/*
 * Experiment : UDP Client-Server - Fibonacci Series
 * Aim        : Client sends a number N to the server; server computes and returns the first N Fibonacci numbers.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5002

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int N;
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &N);
    sendto(sockfd, &N, sizeof(N), 0, (struct sockaddr *)&servaddr, len);

    typedef struct { int n; long long arr[100]; } FibPkt;
    FibPkt pkt;
    recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&servaddr, &len);

    printf("Fibonacci Series: ");
    for (int i = 0; i < pkt.n; i++) printf("%lld ", pkt.arr[i]);
    printf("\n");

    close(sockfd);
    return 0;
}
