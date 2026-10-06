/*
 * Experiment : TCP Client-Server - Sum of N Numbers
 * Aim        : Client sends N numbers to the server; server computes their sum and returns it.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5011

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Sum of N Numbers TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    int N;
    recv(new_socket, &N, sizeof(N), 0);
    float nums[100];
    recv(new_socket, nums, N * sizeof(float), 0);
    printf("N = %d\nNumbers: ", N);
    for (int i = 0; i < N; i++) printf("%.2f ", nums[i]);
    printf("\n");

    float sum = 0;
    for (int i = 0; i < N; i++) sum += nums[i];
    printf("Sum: %.2f\n", sum);

    send(new_socket, &sum, sizeof(sum), 0);

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
Program-Specific Steps: Sum of N Numbers
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Put the server into listening mode to wait for client connections using listen().
5. Accept an incoming client connection using accept().
6. Receive data from the client: Count N and an array of N numbers from client using recv().
7. Process the received data: Compute total sum = num[0] + num[1] + ... + num[N-1].
8. Send the result back to the client: Computed sum value using send().
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
