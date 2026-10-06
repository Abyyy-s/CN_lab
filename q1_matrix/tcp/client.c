/*
 * Experiment : TCP Client-Server - Identify Matrix Type (Upper/Lower/Diagonal)
 * Aim        : Client sends a randomly generated square matrix; server
 *              determines if it is upper triangular, lower triangular, or diagonal.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    int N, matrix[10][10];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter order of matrix (N): ");
    scanf("%d", &N);

    srand(time(0));

    printf("\nGenerated Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 51;   /* 0 to 50 */
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    /* Send N */
    send(sock, &N, sizeof(N), 0);

    /* Send matrix */
    send(sock, matrix, sizeof(matrix), 0);

    char result[50];
    recv(sock, result, sizeof(result), 0);
    printf("\nMatrix Type: %s\n", result);

    close(sock);
    return 0;
}


















































/*
================================================================================
ALGORITHM (TCP Client)
================================================================================

TCP — General Algorithm
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

--------------------------------------------------------------------------------
Program-Specific Steps: Identify Matrix Type (Upper/Lower/Diagonal)
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Establish connection with the server using connect().
5. Read/input required data from user: Matrix order N.
6. Send the data to the server: Generate N x N random matrix elements (0 to 50) using send().
7. Receive the result back from the server using recv().
8. Display the received result: Display generated matrix and matrix type received from server.
9. Close the client socket using close().
10. Stop.

--------------------------------------------------------------------------------
Companion Algorithm (TCP Server — for lab record reference)
--------------------------------------------------------------------------------
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
================================================================================
*/
