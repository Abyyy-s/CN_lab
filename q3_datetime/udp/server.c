/*
 * Experiment : Concurrent Date & Time Server (UDP)
 * Aim        : To implement a concurrent Time Server using UDP socket programming
 *              where the client sends a time request, the server retrieves its
 *              current system time, and sends it back to the client for display.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9002

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char request[20], timeStr[100];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Date & Time UDP Server started on port %d\n", PORT);

    while (1) {
        recvfrom(sockfd, request, sizeof(request), 0, (struct sockaddr *)&cliaddr, &len);

        time_t t = time(NULL);
        strncpy(timeStr, ctime(&t), sizeof(timeStr) - 1);

        printf("Request from client. Sending: %s", timeStr);
        sendto(sockfd, timeStr, strlen(timeStr) + 1, 0, (struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}
