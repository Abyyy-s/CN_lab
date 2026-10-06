/*
 * Experiment : UDP Client-Server - Fibonacci Series
 * Aim        : Client sends a number N to the server; server computes and returns the first N Fibonacci numbers.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5002

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
    printf("Fibonacci Series UDP Server waiting...\n");

    int N;
    recvfrom(sockfd, &N, sizeof(N), 0, (struct sockaddr *)&cliaddr, &len);
    printf("N = %d\n", N);

    long long fib[100];
    fib[0] = 0; fib[1] = 1;
    for (int i = 2; i < N; i++)
        fib[i] = fib[i-1] + fib[i-2];

    printf("Fibonacci series: ");
    for (int i = 0; i < N; i++) printf("%lld ", fib[i]);
    printf("\n");

    typedef struct { int n; long long arr[100]; } FibPkt;
    FibPkt pkt;
    pkt.n = N;
    for (int i = 0; i < N; i++) pkt.arr[i] = fib[i];

    sendto(sockfd, &pkt, sizeof(int) + N * sizeof(long long), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
