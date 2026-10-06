/*
 * Experiment : UDP Client-Server - Average of Three Numbers
 * Aim        : Client sends three numbers to the server; server computes their average and returns it.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5010

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    float nums[3];
    printf("Enter three numbers: ");
    scanf("%f %f %f", &nums[0], &nums[1], &nums[2]);
    sendto(sockfd, nums, sizeof(nums), 0, (struct sockaddr *)&servaddr, len);

    float avg;
    recvfrom(sockfd, &avg, sizeof(avg), 0, (struct sockaddr *)&servaddr, &len);
    printf("Average from Server: %.2f\n", avg);

    close(sockfd);
    return 0;
}
