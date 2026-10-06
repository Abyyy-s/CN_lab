/*
 * Experiment : UDP Client-Server - Palindrome Check
 * Aim        : Client sends a string or number to the server; server checks if it is a palindrome and returns the result.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5004

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
    printf("Enter a string or number to check: ");
    scanf("%s", str);
    sendto(sockfd, str, strlen(str) + 1, 0, (struct sockaddr *)&servaddr, len);

    char result[100];
    recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&servaddr, &len);
    printf("Server says: %s\n", result);

    close(sockfd);
    return 0;
}
