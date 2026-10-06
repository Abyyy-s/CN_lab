/*
 * Experiment : TCP Client-Server - Fibonacci Series
 * Aim        : Client sends a number N to the server; server computes and returns the first N Fibonacci numbers.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5001

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int N;
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &N);
    send(sock, &N, sizeof(N), 0);

    int terms;
    long long fib[100];
    recv(sock, &terms, sizeof(terms), 0);
    recv(sock, fib, terms * sizeof(long long), 0);

    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) printf("%lld ", fib[i]);
    printf("\n");

    close(sock);
    return 0;
}
