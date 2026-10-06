/*
 * Experiment : UDP Client-Server - String Reverse
 * Aim        : Client sends a string to the server; server reverses it and returns the result.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5014

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
    printf("String Reverse UDP Server waiting...\n");

    char str[256];
    recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %s\n", str);

    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char tmp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = tmp;
    }
    printf("Reversed: %s\n", str);

    sendto(sockfd, str, strlen(str) + 1, 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);
    return 0;
}
