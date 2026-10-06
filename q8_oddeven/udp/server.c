/*
 * Experiment : UDP Client-Server - Odd or Even Check
 * Aim        : Client sends a number to the server; server checks if it is odd or even and returns the result.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5008

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
    printf("Odd or Even Check UDP Server waiting...\n");

    int num;
    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %d\n", num);

    char result[100];
    snprintf(result, sizeof(result), "%d is %s.", num, (num % 2 == 0) ? "Even" : "Odd");

    sendto(sockfd, result, strlen(result) + 1, 0, (struct sockaddr *)&cliaddr, len);
    printf("Result: %s\n", result);

    close(sockfd);
    return 0;
}
