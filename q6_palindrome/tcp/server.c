/*
 * Experiment : TCP Client-Server - Palindrome Check
 * Aim        : Client sends a string or number to the server; server checks if it is a palindrome and returns the result.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5003

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

    printf("Palindrome Check TCP Server waiting...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    printf("Client connected.\n");

    char str[256];
    recv(new_socket, str, sizeof(str), 0);
    printf("Received: %s\n", str);

    int n = strlen(str);
    int isPalin = 1;
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - 1 - i]) { isPalin = 0; break; }
    }
    char result[100];
    snprintf(result, sizeof(result), "\"%s\" is %s a palindrome.", str, isPalin ? "" : "NOT");

    send(new_socket, result, strlen(result) + 1, 0);
    printf("Result: %s\n", result);

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
Program-Specific Steps: Palindrome Check (String / Number)
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Put the server into listening mode to wait for client connections using listen().
5. Accept an incoming client connection using accept().
6. Receive data from the client: String or number representation from client using recv().
7. Process the received data: Check if string reads identical forwards and backwards by comparing characters from both ends.
8. Send the result back to the client: Result message stating whether the input is a palindrome using send().
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
