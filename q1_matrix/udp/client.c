/*
 * Experiment : UDP Client-Server - Identify Matrix Type (Upper/Lower/Diagonal)
 * File       : client.c  (UDP Client)
 * Compile    : gcc client.c -o client
 * Run        : ./client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12346

typedef struct {
    int N;
    int matrix[10][10];
} Packet;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    Packet pkt;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter order of matrix (N): ");
    scanf("%d", &pkt.N);

    srand(time(0));
    printf("\nGenerated Matrix:\n");
    for (int i = 0; i < pkt.N; i++) {
        for (int j = 0; j < pkt.N; j++) {
            pkt.matrix[i][j] = rand() % 51;
            printf("%3d ", pkt.matrix[i][j]);
        }
        printf("\n");
    }

    sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&servaddr, len);

    char result[50];
    recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr *)&servaddr, &len);
    printf("\nMatrix Type: %s\n", result);

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
Program-Specific Steps: Identify Matrix Type (Upper/Lower/Diagonal)
--------------------------------------------------------------------------------
1. Start.
2. Create a UDP socket using socket(AF_INET, SOCK_DGRAM, 0).
3. Specify server IP address ("127.0.0.1") and designated port number.
4. Read/input required data from user: Matrix order N.
5. Send the data to the server: Generate N x N random matrix elements (0 to 50) using sendto().
6. Receive the result back from the server using recvfrom().
7. Display the received result: Display generated matrix and matrix type received from server.
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
