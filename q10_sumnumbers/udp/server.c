/*
 * Experiment : UDP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5012

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
    printf("Sum of N Numbers UDP Server waiting...\n");

    typedef struct { int N; float nums[100]; } NumPkt;
    NumPkt pkt;
    recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&cliaddr, &len);
    int N = pkt.N;
    printf("N = %d\nNumbers: ", N);
    for (int i = 0; i < N; i++) printf("%.2f ", pkt.nums[i]);
    printf("\n");

    float sum = 0;
    for (int i = 0; i < N; i++) sum += pkt.nums[i];
    printf("Sum: %.2f\n", sum);

    sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&cliaddr, len);

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
Program-Specific Steps: Sum of N Numbers
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Receive data from the client: Count N and an array of N numbers from client using recvfrom().
5. Process the received data: Compute total sum = num[0] + num[1] + ... + num[N-1].
6. Send the result back to the client: Computed sum value using sendto().
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
