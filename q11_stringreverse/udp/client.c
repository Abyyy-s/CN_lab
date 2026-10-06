/*
 * Experiment : UDP Client-Server - String Reverse
 * Aim        : Client sends a string to the server; server reverses it and returns the result.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5014

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char str[256];
    printf("Enter a string to reverse: ");
    scanf("%255s", str);
    sendto(sockfd, str, strlen(str) + 1, 0, (struct sockaddr *)&servaddr, len);

    char reversed[256];
    recvfrom(sockfd, reversed, sizeof(reversed), 0, (struct sockaddr *)&servaddr, &len);
    printf("Reversed string: %s\n", reversed);

    close(sockfd);
    return 0;
}
