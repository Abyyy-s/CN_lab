/*
 * Experiment : TCP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5011

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int N;
    printf("How many numbers? ");
    scanf("%d", &N);
    float nums[100];
    printf("Enter %d numbers: ", N);
    for (int i = 0; i < N; i++) scanf("%f", &nums[i]);
    send(sock, &N, sizeof(N), 0);
    send(sock, nums, N * sizeof(float), 0);

    float sum;
    recv(sock, &sum, sizeof(sum), 0);
    printf("Sum from Server: %.2f\n", sum);

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
Program-Specific Steps: Sum of N Numbers
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Establish connection with the server using connect().
5. Read/input required data from user: Count N and N numbers entered by user.
6. Send the data to the server: Send count N and array of numbers to server using send().
7. Receive the result back from the server using recv().
8. Display the received result: Display total sum received from server.
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
