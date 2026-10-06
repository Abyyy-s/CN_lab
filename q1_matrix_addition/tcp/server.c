/*
 * Experiment : TCP Client-Server - Matrix Addition
 * Aim        : Client sends two matrices; server computes their sum and returns it.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12347

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    MatPair mp;
    int result[10][10];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Matrix Addition TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    recv(new_socket, &mp, sizeof(mp), 0);

    int N = mp.N;
    printf("\nMatrix A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.A[i][j]);
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", mp.B[i][j]);
        printf("\n");
    }

    /* Compute A + B */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = mp.A[i][j] + mp.B[i][j];

    printf("\nResult (A + B):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", result[i][j]);
        printf("\n");
    }

    /* Send back N and result */
    send(new_socket, &N, sizeof(N), 0);
    send(new_socket, result, sizeof(result), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}


















































/*
================================================================================
ALGORITHM (TCP Server)
================================================================================

TCP — General Algorithm
TCP Server:
1. Start.
2. Create a socket using socket().
3. Assign IP address and port number using bind().
4. Wait for client connection using listen().
5. Accept the client connection using accept().
6. Receive data from the client using recv()/read().
7. Process the received data.
8. Send the result back using send()/write().
9. Close the client socket.
10. Close the server socket.
11. Stop.

--------------------------------------------------------------------------------
Program-Specific Steps: Matrix Addition
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Put the server into listening mode to wait for client connections using listen().
5. Accept an incoming client connection using accept().
6. Receive data from the client: Matrix order N and two matrices A and B of size N x N using recv().
7. Process the received data: Compute element-wise sum: Result[i][j] = A[i][j] + B[i][j].
8. Send the result back to the client: Resultant sum matrix (A + B) using send().
9. Close the active client connection socket using close().
10. Close the server listening socket using close().
11. Stop.

--------------------------------------------------------------------------------
Companion Algorithm (TCP Client — for lab record reference)
--------------------------------------------------------------------------------
TCP Client:
1. Start.
2. Create a socket using socket().
3. Specify the server IP address and port number.
4. Establish connection using connect().
5. Read/input the required data.
6. Send data to the server using send()/write().
7. Receive the result using recv()/read().
8. Display the result.
9. Close the socket.
10. Stop.
================================================================================
*/
