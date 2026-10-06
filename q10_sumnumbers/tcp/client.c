/*
 * Experiment : TCP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5011

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int N;
    printf("How many numbers? ");
    scanf("%d", &N);
    float nums[100];
    printf("Enter %d numbers: ", N);
    for (int i = 0; i < N; i++) scanf("%f", &nums[i]);
    send(sock, &N, sizeof(N), 0);
    send(sock, nums, N * sizeof(float), 0);

    float sum;
    recv(sock, &sum, sizeof(sum), 0);
    printf("Sum from Server: %.2f\n", sum);

    close(sock);
    return 0;
}
