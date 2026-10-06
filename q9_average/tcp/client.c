/*
 * Experiment : TCP Client-Server - Average of Three Numbers
 * Aim        : Client sends three numbers to the server; server computes their average and returns it.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5009

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    float nums[3];
    printf("Enter three numbers: ");
    scanf("%f %f %f", &nums[0], &nums[1], &nums[2]);
    send(sock, nums, sizeof(nums), 0);

    float avg;
    recv(sock, &avg, sizeof(avg), 0);
    printf("Average from Server: %.2f\n", avg);

    close(sock);
    return 0;
}
