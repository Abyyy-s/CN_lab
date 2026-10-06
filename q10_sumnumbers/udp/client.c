/*
 * Experiment : UDP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5012

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    typedef struct { int N; float nums[100]; } NumPkt;
    NumPkt pkt;
    printf("How many numbers? ");
    scanf("%d", &pkt.N);
    printf("Enter %d numbers: ", pkt.N);
    for (int i = 0; i < pkt.N; i++) scanf("%f", &pkt.nums[i]);
    sendto(sockfd, &pkt, sizeof(int) + pkt.N * sizeof(float), 0, (struct sockaddr *)&servaddr, len);

    float sum;
    recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&servaddr, &len);
    printf("Sum from Server: %.2f\n", sum);

    close(sockfd);
    return 0;
}


















































/*
================================================================================
ALGORITHM (UDP Client)
================================================================================

UDP — General Algorithm
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

--------------------------------------------------------------------------------
Program-Specific Steps: Sum of N Numbers
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Count N and N numbers entered by user.
5. Send the data to the server: Send count N and array of numbers to server using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display total sum received from server.
8. Close the UDP socket using close().
9. Stop.

--------------------------------------------------------------------------------
Companion Algorithm (UDP Server — for lab record reference)
--------------------------------------------------------------------------------
UDP Server:
1. Start.
2. Create a socket using socket().
3. Assign IP address and port number using bind().
4. Receive data from the client using recvfrom().
5. Process the received data.
6. Send the result back using sendto().
7. Close the socket.
8. Stop.
================================================================================
*/
