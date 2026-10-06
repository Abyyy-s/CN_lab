/*
 * Experiment : Multi-user Chat Server using UDP
 * Aim        : To implement a multi-user chat server using UDP socket programming
 *              where multiple clients communicate simultaneously through a central
 *              server. The server tracks all registered clients and broadcasts
 *              every message it receives to all other clients.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 *
 * Note       : UDP is connectionless. Clients register themselves by sending
 *              "JOIN:<name>" first. The server maintains a list of known client
 *              addresses and broadcasts every message to all others.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT        8889
#define MAX_CLIENTS 10
#define BUFFER      1024

typedef struct {
    struct sockaddr_in addr;
    char name[32];
    int  active;
} Client;

Client clients[MAX_CLIENTS];
int    nclients = 0;

/* Find existing client by address; returns index or -1 */
int find_client(struct sockaddr_in *addr) {
    for (int i = 0; i < nclients; i++) {
        if (clients[i].active &&
            clients[i].addr.sin_addr.s_addr == addr->sin_addr.s_addr &&
            clients[i].addr.sin_port        == addr->sin_port)
            return i;
    }
    return -1;
}

/* Broadcast msg to all clients except sender (index skip) */
void broadcast(int sockfd, const char *msg, int skip) {
    for (int i = 0; i < nclients; i++) {
        if (i != skip && clients[i].active)
            sendto(sockfd, msg, strlen(msg), 0,
                   (struct sockaddr *)&clients[i].addr,
                   sizeof(clients[i].addr));
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[BUFFER], outbuf[BUFFER + 64];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Multi-user Chat UDP Server started on port %d\n", PORT);
    printf("Clients should send JOIN:<name> to register.\n\n");

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER - 1, 0,
                         (struct sockaddr *)&cliaddr, &len);
        if (n <= 0) continue;
        buffer[n] = '\0';

        /* Check for JOIN message */
        if (strncmp(buffer, "JOIN:", 5) == 0) {
            int idx = find_client(&cliaddr);
            if (idx == -1 && nclients < MAX_CLIENTS) {
                clients[nclients].addr   = cliaddr;
                clients[nclients].active = 1;
                strncpy(clients[nclients].name, buffer + 5, 31);
                clients[nclients].name[31] = '\0';
                printf("[+] New client: %s (socket %s:%d)\n",
                       clients[nclients].name,
                       inet_ntoa(cliaddr.sin_addr),
                       ntohs(cliaddr.sin_port));

                /* Welcome message to the new client */
                char welcome[128];
                snprintf(welcome, sizeof(welcome),
                         "[Server] Welcome %s! You are now in the chat.\n",
                         clients[nclients].name);
                sendto(sockfd, welcome, strlen(welcome), 0,
                       (struct sockaddr *)&cliaddr, len);

                /* Announce to others */
                snprintf(outbuf, sizeof(outbuf),
                         "[Server] %s joined the chat.\n",
                         clients[nclients].name);
                broadcast(sockfd, outbuf, nclients);
                nclients++;
            } else {
                char already[] = "[Server] You are already registered.\n";
                sendto(sockfd, already, strlen(already), 0,
                       (struct sockaddr *)&cliaddr, len);
            }
            continue;
        }

        /* Check for QUIT message */
        if (strncmp(buffer, "QUIT", 4) == 0) {
            int idx = find_client(&cliaddr);
            if (idx != -1) {
                printf("[-] Client left: %s\n", clients[idx].name);
                snprintf(outbuf, sizeof(outbuf),
                         "[Server] %s has left the chat.\n",
                         clients[idx].name);
                clients[idx].active = 0;
                broadcast(sockfd, outbuf, idx);
            }
            continue;
        }

        /* Regular chat message — broadcast to all others */
        int idx = find_client(&cliaddr);
        if (idx != -1) {
            printf("[%s]: %s\n", clients[idx].name, buffer);
            snprintf(outbuf, sizeof(outbuf), "[%s]: %s",
                     clients[idx].name, buffer);
            broadcast(sockfd, outbuf, idx);
        } else {
            /* Unregistered client — ask to join */
            char notreg[] = "[Server] Please register first with JOIN:<yourname>\n";
            sendto(sockfd, notreg, strlen(notreg), 0,
                   (struct sockaddr *)&cliaddr, len);
        }
    }

    close(sockfd);
    return 0;
}
