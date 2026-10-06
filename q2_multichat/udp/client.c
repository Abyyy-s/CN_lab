/*
 * Experiment : Multi-user Chat Client using UDP
 * Aim        : To implement a multi-user chat client using UDP socket programming
 *              that registers with the server, sends messages, and receives
 *              broadcast messages from other clients via the server.
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 *
 * Protocol   :
 *   - On start  : send "JOIN:<name>"
 *   - To chat   : send any text message
 *   - To quit   : type "QUIT" and press Enter
 *
 * Uses select() to simultaneously listen for incoming messages (from server)
 * and user keyboard input — so chat is truly interactive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT   8889
#define BUFFER 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    char buffer[BUFFER], name[32], joinmsg[64];
    fd_set readfds;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Register with server */
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    snprintf(joinmsg, sizeof(joinmsg), "JOIN:%s", name);
    sendto(sockfd, joinmsg, strlen(joinmsg), 0,
           (struct sockaddr *)&servaddr, len);

    printf("Joined chat as [%s]. Type messages below (type QUIT to exit):\n\n", name);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);   /* keyboard input */
        FD_SET(sockfd,       &readfds);   /* incoming from server */

        select(sockfd + 1, &readfds, NULL, NULL, NULL);

        /* Message received from server (another client's broadcast) */
        if (FD_ISSET(sockfd, &readfds)) {
            int n = recvfrom(sockfd, buffer, BUFFER - 1, 0,
                             (struct sockaddr *)&servaddr, &len);
            if (n > 0) {
                buffer[n] = '\0';
                printf("%s", buffer);
                fflush(stdout);
            }
        }

        /* User typed a message */
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (!fgets(buffer, BUFFER, stdin)) break;
            buffer[strcspn(buffer, "\n")] = '\n';  /* keep newline for display */

            /* Handle QUIT */
            if (strncmp(buffer, "QUIT", 4) == 0) {
                sendto(sockfd, "QUIT", 4, 0,
                       (struct sockaddr *)&servaddr, len);
                printf("You left the chat.\n");
                break;
            }

            /* Strip trailing newline before sending */
            buffer[strcspn(buffer, "\n")] = '\0';
            sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&servaddr, len);
        }
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
Program-Specific Steps: Multi-user Chat Server
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Chat messages typed by the user from standard input (stdin).
5. Send the data to the server: Use select() to simultaneously monitor keyboard input and incoming server messages without blocking using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display incoming broadcast chat messages from other clients.
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
