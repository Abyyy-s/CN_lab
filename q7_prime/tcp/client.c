/*
 * Experiment : TCP Client-Server - Prime or Composite Check
 * Aim        : Client sends a number to the server; server checks if it is prime or composite and returns the result.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5005

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    send(sock, &num, sizeof(num), 0);

    char result[100];
    recv(sock, result, sizeof(result), 0);
    printf("Server says: %s\n", result);

    close(sock);
    return 0;
}
