/*
 * Experiment : UDP Client-Server - Average of Three Numbers
 * Aim        : Client sends three numbers to the server; server computes their average and returns it.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5010

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
    printf("Average of Three Numbers UDP Server waiting...\n");

    float nums[3];
    recvfrom(sockfd, nums, sizeof(nums), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %.2f, %.2f, %.2f\n", nums[0], nums[1], nums[2]);

    float avg = (nums[0] + nums[1] + nums[2]) / 3.0;
    printf("Average: %.2f\n", avg);

    sendto(sockfd, &avg, sizeof(avg), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
