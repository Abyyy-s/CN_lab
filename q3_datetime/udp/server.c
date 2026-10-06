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
Program-Specific Steps: Concurrent Date and Time Server
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Receive data from the client: Time request message from client using recvfrom().
5. Process the received data: Retrieve current system time using time() and format using ctime() (uses fork() for concurrent handling in TCP).
6. Send the result back to the client: Formatted date and time string using sendto().
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
