/*
 * Experiment : TCP Client-Server - String Reverse
 * Aim        : Client sends a string to the server; server reverses it and returns the result.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5013

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    char str[256];
    printf("Enter a string to reverse: ");
    scanf("%255s", str);
    send(sock, str, strlen(str) + 1, 0);

    char reversed[256];
    recv(sock, reversed, sizeof(reversed), 0);
    printf("Reversed string: %s\n", reversed);

    close(sock);
    return 0;
}
