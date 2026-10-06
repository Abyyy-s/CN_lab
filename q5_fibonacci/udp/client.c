/*
 * Experiment : UDP Client-Server - Fibonacci Series
 * Aim        : Client sends a number N to the server; server computes and returns the first N Fibonacci numbers.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5002

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int N;
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &N);
    sendto(sockfd, &N, sizeof(N), 0, (struct sockaddr *)&servaddr, len);

    typedef struct { int n; long long arr[100]; } FibPkt;
    FibPkt pkt;
    recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&servaddr, &len);

    printf("Fibonacci Series: ");
    for (int i = 0; i < pkt.n; i++) printf("%lld ", pkt.arr[i]);
    printf("\n");

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
Program-Specific Steps: Fibonacci Series Generation
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Number of terms N entered by user.
5. Send the data to the server: Send N to server using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display the Fibonacci series received from server.
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
