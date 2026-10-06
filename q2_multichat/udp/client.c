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
