/*
 * Experiment : UDP Client-Server - Factorial
 * Aim        : Client sends a number N to the server; server computes N! and returns the result.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5016

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
    printf("Factorial UDP Server waiting...\n");

    int N;
    recvfrom(sockfd, &N, sizeof(N), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %d\n", N);

    long long fact = 1;
    for (int i = 2; i <= N; i++) fact *= i;
    printf("%d! = %lld\n", N, fact);

    sendto(sockfd, &fact, sizeof(fact), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
