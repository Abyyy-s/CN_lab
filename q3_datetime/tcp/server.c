/*
 * Experiment : Concurrent Date & Time Server (TCP)
 * Aim        : To implement a concurrent Time Server using TCP socket programming
 *              where the client sends a time request to the server, the server
 *              retrieves its current system time, and sends it back to the client.
 * File       : server.c  (TCP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define PORT 9001

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
    listen(server_fd, 5);

    printf("Date & Time TCP Server started on port %d\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        /* Fork for concurrent handling */
        pid_t pid = fork();
        if (pid == 0) {
            /* Child process */
            close(server_fd);

            char request[20];
            recv(new_socket, request, sizeof(request), 0);

            time_t t = time(NULL);
            char *timeStr = ctime(&t);

            printf("Request received. Sending time: %s", timeStr);
            send(new_socket, timeStr, strlen(timeStr) + 1, 0);

            close(new_socket);
            exit(0);
        } else {
            /* Parent process */
            close(new_socket);
            waitpid(-1, NULL, WNOHANG);
        }
    }

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
Program-Specific Steps: Concurrent Date and Time Server
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Assign local IP address (INADDR_ANY) and designated port number using bind().
4. Put the server into listening mode to wait for client connections using listen().
5. Accept an incoming client connection using accept().
6. Receive data from the client: Time request message from client using recv().
7. Process the received data: Retrieve current system time using time() and format using ctime() (uses fork() for concurrent handling in TCP).
8. Send the result back to the client: Formatted date and time string using send().
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
