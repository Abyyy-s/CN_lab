/*
 * Experiment : UDP Client-Server - Matrix Multiplication
 * Aim        : To implement a UDP client-server program where the client sends
 *              two randomly generated square matrices to the server, and the
 *              server computes their product and sends the result back.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12350

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
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    MatPair mp;
    MatResult mr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter order of matrices (N x N): ");
    scanf("%d", &mp.N);

    srand(time(0));

    printf("\nMatrix A:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.A[i][j] = rand() % 10;   /* 0 to 9 for readable products */
            printf("%4d ", mp.A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.B[i][j] = rand() % 10;
            printf("%4d ", mp.B[i][j]);
        }
        printf("\n");
    }

    /* Send both matrices to server */
    sendto(sockfd, &mp, sizeof(mp), 0, (struct sockaddr *)&servaddr, len);

    /* Receive result */
    recvfrom(sockfd, &mr, sizeof(mr), 0, (struct sockaddr *)&servaddr, &len);

    printf("\nResult (A x B) from Server:\n");
    for (int i = 0; i < mr.N; i++) {
        for (int j = 0; j < mr.N; j++)
            printf("%6d ", mr.R[i][j]);
        printf("\n");
    }

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
Program-Specific Steps: Matrix Multiplication
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Matrix order N.
5. Send the data to the server: Generate two random matrices A and B of size N x N using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display matrices A, B and resultant product matrix received from server.
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
