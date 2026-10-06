/*
 * Experiment : UDP Abbreviation Expander Client
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT   9003
#define BUFFER 2048

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    char sentence[BUFFER], result[BUFFER * 2];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence with abbreviations: ");
    fgets(sentence, BUFFER, stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    sendto(sockfd, sentence, strlen(sentence), 0, (struct sockaddr *)&servaddr, len);

    int n = recvfrom(sockfd, result, sizeof(result) - 1, 0, (struct sockaddr *)&servaddr, &len);
    result[n] = '\0';
    printf("Expanded sentence: %s\n", result);

    close(sockfd);
    return 0;
}
