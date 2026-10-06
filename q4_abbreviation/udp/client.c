/*
 * Experiment : UDP Abbreviation Expander Client
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT   9003
#define BUFFER 2048

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    char sentence[BUFFER], result[BUFFER * 2];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence with abbreviations: ");
    fgets(sentence, BUFFER, stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    sendto(sockfd, sentence, strlen(sentence), 0, (struct sockaddr *)&servaddr, len);

    int n = recvfrom(sockfd, result, sizeof(result) - 1, 0, (struct sockaddr *)&servaddr, &len);
    result[n] = '\0';
    printf("Expanded sentence: %s\n", result);

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
Program-Specific Steps: Abbreviation Expander (Slang to Formal English)
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Sentence containing abbreviations entered by user.
5. Send the data to the server: Send input sentence to UDP server using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display expanded formal English sentence received from server.
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
