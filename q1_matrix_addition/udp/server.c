/*
 * Experiment : UDP Client-Server - Matrix Addition
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12348

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

typedef struct {
    int N;
    int R[10][10];
} MatResult;

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    MatPair mp;
    MatResult mr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Matrix Addition UDP Server waiting...\n");

    recvfrom(sockfd, &mp, sizeof(mp), 0, (struct sockaddr *)&cliaddr, &len);

    int N = mp.N;
    mr.N = N;
    printf("\nReceived Matrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.A[i][j]);
        printf("\n");
    }
    printf("\nReceived Matrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.B[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mr.R[i][j] = mp.A[i][j] + mp.B[i][j];

    printf("\nResult (A + B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mr.R[i][j]);
        printf("\n");
    }

    sendto(sockfd, &mr, sizeof(mr), 0, (struct sockaddr *)&cliaddr, len);

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
Program-Specific Steps: Matrix Addition
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Receive data from the client: Matrix order N and two matrices A and B of size N x N using recvfrom().
5. Process the received data: Compute element-wise sum: Result[i][j] = A[i][j] + B[i][j].
6. Send the result back to the client: Resultant sum matrix (A + B) using sendto().
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
