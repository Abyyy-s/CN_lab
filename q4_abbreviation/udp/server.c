/*
 * Experiment : UDP Abbreviation Expander Server
 * Aim        : To design and implement a UDP client-server program where the
 *              client sends a sentence with abbreviations and the server
 *              translates them into formal English.
 * File       : server.c  (UDP Server)
 * Compile    : gcc server.c -o server
 * Run        : ./server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT   9003
#define BUFFER 2048

/* Abbreviation dictionary */
typedef struct {
    char abbr[10];
    char full[50];
} DictEntry;

DictEntry dict[] = {
    {"tbh",  "to be honest"},
    {"ig",   "I guess"},
    {"tbf",  "to be fair"},
    {"atm",  "at the moment"},
    {"irl",  "in real life"},
    {"lol",  "laughing out loud"},
    {"asap", "as soon as possible"},
    {"omg",  "oh my God"},
    {"ttyl", "talk to you later"},
    {"idk",  "I don't know"},
    {"nvm",  "never mind"},
    {"idc",  "I don't care"},
    {"",     ""}   /* sentinel */
};

/* Expand abbreviations in sentence */
void expand(const char *in, char *out) {
    char word[100], lower[100];
    int oi = 0;
    int i = 0, n = strlen(in);

    while (i <= n) {
        /* Collect a word */
        int wi = 0;
        while (i <= n && (isalpha((unsigned char)in[i]) || in[i] == '\'')) {
            word[wi++] = in[i++];
        }
        word[wi] = '\0';

        if (wi > 0) {
            /* lowercase for lookup */
            for (int k = 0; k < wi; k++) lower[k] = tolower((unsigned char)word[k]);
            lower[wi] = '\0';

            int found = 0;
            for (int d = 0; dict[d].abbr[0] != '\0'; d++) {
                if (strcmp(lower, dict[d].abbr) == 0) {
                    int fl = strlen(dict[d].full);
                    memcpy(out + oi, dict[d].full, fl);
                    oi += fl;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                memcpy(out + oi, word, wi);
                oi += wi;
            }
        }

        /* Copy non-alpha character */
        if (i < n) {
            out[oi++] = in[i++];
        } else {
            i++;
        }
    }
    out[oi] = '\0';
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[BUFFER], result[BUFFER * 2];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Abbreviation Expander UDP Server started on port %d\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER - 1, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);

        expand(buffer, result);
        printf("Expanded: %s\n", result);

        sendto(sockfd, result, strlen(result) + 1, 0, (struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);
    return 0;
}
