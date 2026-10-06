/*
 * Experiment : UDP Client-Server - Palindrome Check
 * Aim        : Client sends a string or number to the server; server checks if it is a palindrome and returns the result.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5004

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
    printf("Palindrome Check UDP Server waiting...\n");

    char str[256];
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %s\n", str);

    int n = strlen(str);
    int isPalin = 1;
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - 1 - i]) { isPalin = 0; break; }
    }
    char result[100];
    snprintf(result, sizeof(result), "\"%s\" is %s a palindrome.", str, isPalin ? "" : "NOT");

    sendto(sockfd, result, strlen(result) + 1, 0, (struct sockaddr *)&cliaddr, len);
    printf("Result: %s\n", result);

    close(sockfd);
    return 0;
}
