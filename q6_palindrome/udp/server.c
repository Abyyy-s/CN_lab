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


















































/*
================================================================================
ALGORITHM (UDP Server)
================================================================================

UDP — General Algorithm
UDP Server:
1. Start.
2. Create a socket using socket().
3. Assign IP address and port number using bind().
4. Receive data from the client using recvfrom().
5. Process the received data.
6. Send the result back using sendto().
7. Close the socket.
8. Stop.

--------------------------------------------------------------------------------
Program-Specific Steps: Palindrome Check (String / Number)
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Receive data from the client: String or number representation from client using recvfrom().
5. Process the received data: Check if string reads identical forwards and backwards by comparing characters from both ends.
6. Send the result back to the client: Result message stating whether the input is a palindrome using sendto().
7. Close the UDP socket using close().
8. Stop.

--------------------------------------------------------------------------------
Companion Algorithm (UDP Client — for lab record reference)
--------------------------------------------------------------------------------
UDP Client:
1. Start.
2. Create a socket using socket().
3. Specify the server IP address and port number.
4. Read/input the required data.
5. Send data to the server using sendto().
6. Receive the result using recvfrom().
7. Display the result.
8. Close the socket.
9. Stop.
================================================================================
*/
