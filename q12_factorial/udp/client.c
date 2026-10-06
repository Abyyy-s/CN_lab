/*
 * Experiment : UDP Client-Server - Factorial
 * Aim        : Client sends a number N to the server; server computes N! and returns the result.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5016

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
    printf("Enter a number to find factorial: ");
    scanf("%d", &N);
    sendto(sockfd, &N, sizeof(N), 0, (struct sockaddr *)&servaddr, len);

    long long fact;
    recvfrom(sockfd, &fact, sizeof(fact), 0, (struct sockaddr *)&servaddr, &len);
    printf("Factorial from Server: %lld\n", fact);

    close(sockfd);
    return 0;
}
