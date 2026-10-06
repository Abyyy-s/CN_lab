/*
 * Experiment : Multi-user Chat Client (TCP)
 * File       : client.c  (TCP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT   8888
#define BUFFER 1024

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER];
    fd_set readfds;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connected to chat server. Type messages below:\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sock, &readfds);

        select(sock + 1, &readfds, NULL, NULL, NULL);

        /* Message from server */
        if (FD_ISSET(sock, &readfds)) {
            int n = read(sock, buffer, BUFFER - 1);
            if (n <= 0) {
                printf("Server disconnected.\n");
                break;
            }
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        /* User input */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            fgets(buffer, BUFFER, stdin);
            send(sock, buffer, strlen(buffer), 0);
        }
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
Program-Specific Steps: Multi-user Chat Server
--------------------------------------------------------------------------------
1. Start.
2. Create a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Establish connection with the server using connect().
5. Read/input required data from user: Chat messages typed by the user from standard input (stdin).
6. Send the data to the server: Use select() to simultaneously monitor keyboard input and incoming server messages without blocking using send().
7. Receive the result back from the server using recv().
8. Display the received result: Display incoming broadcast chat messages from other clients.
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
