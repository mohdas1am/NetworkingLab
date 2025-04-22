#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }

    printf("Connected to server.\n");

    // Send "start"
    printf("Type 'start' to begin session: ");
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

    send(sockfd, buffer, strlen(buffer), 0);
    int bytes = recv(sockfd, buffer, BUF_SIZE, 0);
    buffer[bytes] = '\0';
    printf("Server: %s", buffer);

    if (strstr(buffer, "Invalid")) {
        close(sockfd);
        return 0;
    }

    while (1) {
        printf("\nYour message: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

        send(sockfd, buffer, strlen(buffer), 0);

        bytes = recv(sockfd, buffer, BUF_SIZE, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';

        printf("Server: %s", buffer);

        if (strstr(buffer, "ended")) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

