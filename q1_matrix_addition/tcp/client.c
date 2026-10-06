/*
 * Experiment : TCP Client-Server - Matrix Addition
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12347

typedef struct {
    int N;
    int A[10][10];
    int B[10][10];
} MatPair;

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    MatPair mp;
    int result[10][10];
    int N;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter order of matrix (N): ");
    scanf("%d", &mp.N);

    srand(time(0));

    printf("\nMatrix A:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.A[i][j] = rand() % 51;
            printf("%3d ", mp.A[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (int i = 0; i < mp.N; i++) {
        for (int j = 0; j < mp.N; j++) {
            mp.B[i][j] = rand() % 51;
            printf("%3d ", mp.B[i][j]);
        }
        printf("\n");
    }

    send(sock, &mp, sizeof(mp), 0);

    recv(sock, &N, sizeof(N), 0);
    recv(sock, result, sizeof(result), 0);

    printf("\nResult (A + B) from Server:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", result[i][j]);
        printf("\n");
    }

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
Program-Specific Steps: Matrix Addition
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Establish connection with the server using connect().
5. Read/input required data from user: Matrix order N.
6. Send the data to the server: Generate two random matrices A and B of size N x N using send().
7. Receive the result back from the server using recv().
8. Display the received result: Display matrices A, B and resultant sum matrix received from server.
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
