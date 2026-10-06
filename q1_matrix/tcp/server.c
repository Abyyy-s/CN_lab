/*
 * Experiment : TCP Client-Server - Identify Matrix Type (Upper/Lower/Diagonal)
 * Aim        : Client sends a randomly generated square matrix; server
 *              determines if it is upper triangular, lower triangular, or diagonal.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int N, matrix[10][10];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server waiting for connection...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    /* Receive N */
    recv(new_socket, &N, sizeof(N), 0);

    /* Receive matrix */
    recv(new_socket, matrix, sizeof(matrix), 0);

    printf("\nReceived %dx%d Matrix:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }

    int upper = 1, lower = 1, diagonal = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > j && matrix[i][j] != 0) upper    = 0;
            if (i < j && matrix[i][j] != 0) lower    = 0;
            if (i != j && matrix[i][j] != 0) diagonal = 0;
        }
    }

    char result[50];
    if (diagonal)       strcpy(result, "Diagonal Matrix");
    else if (upper)     strcpy(result, "Upper Triangular Matrix");
    else if (lower)     strcpy(result, "Lower Triangular Matrix");
    else                strcpy(result, "Not a Special Matrix");

    printf("Result: %s\n", result);
    send(new_socket, result, strlen(result) + 1, 0);

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
Program-Specific Steps: Identify Matrix Type (Upper/Lower/Diagonal)
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Put the server into listening mode to wait for client connections using listen().
5. Accept an incoming client connection using accept().
6. Receive data from the client: Matrix order N and N x N integer matrix elements using recv().
7. Process the received data: Check conditions for Diagonal (i != j is 0), Upper Triangular (i > j is 0), Lower Triangular (i < j is 0).
8. Send the result back to the client: String representing matrix classification result using send().
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
