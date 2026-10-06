/*
 * Experiment : UDP Client-Server - Average of Three Numbers
 * Aim        : Client sends three numbers to the server; server computes their average and returns it.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5010

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
    printf("Average of Three Numbers UDP Server waiting...\n");

    float nums[3];
    recvfrom(sockfd, nums, sizeof(nums), 0, (struct sockaddr *)&cliaddr, &len);
    printf("Received: %.2f, %.2f, %.2f\n", nums[0], nums[1], nums[2]);

    float avg = (nums[0] + nums[1] + nums[2]) / 3.0;
    printf("Average: %.2f\n", avg);

    sendto(sockfd, &avg, sizeof(avg), 0, (struct sockaddr *)&cliaddr, len);

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
Program-Specific Steps: Average of Three Numbers
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Receive data from the client: Three float numbers from client using recvfrom().
5. Process the received data: Compute average = (num1 + num2 + num3) / 3.0.
6. Send the result back to the client: Computed average value (float) using sendto().
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
