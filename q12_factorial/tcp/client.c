/*
 * Experiment : TCP Client-Server - Factorial
 * Aim        : Client sends a number N to the server; server computes N! and returns the result.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5015

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int N;
    printf("Enter a number to find factorial: ");
    scanf("%d", &N);
    send(sock, &N, sizeof(N), 0);

    long long fact;
    recv(sock, &fact, sizeof(fact), 0);
    printf("Factorial from Server: %lld\n", fact);

    close(sock);
    return 0;
}
