#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080
#define BUF_SIZE 1024
#define WORD_LIMIT 25

void *handle_client(void *client_socket) {
    int sock = *(int *)client_socket;
    free(client_socket);

    char buffer[BUF_SIZE];
    int word_count = 0;

    // Wait for client to send "start"
    int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
    buffer[bytes_received] = '\0';

    if (strcmp(buffer, "start") != 0) {
        char msg[] = "Invalid start. Connection closing.\n";
        send(sock, msg, strlen(msg), 0);
        close(sock);
        pthread_exit(NULL);
    }

    send(sock, "Session started. You may send messages.\n", 40, 0);
    printf("Client session started.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;

        buffer[bytes] = '\0';

        // Check for "stop" command
        if (strcmp(buffer, "stop") == 0) {
            send(sock, "Session stopped. Goodbye!\n", 27, 0);
            printf("Client ended the session.\n");
            break;
        }

        // Count words
        int count = 0;
        char temp_buf[BUF_SIZE];
        strcpy(temp_buf, buffer);
        char *token = strtok(temp_buf, " \n");
        while (token != NULL) {
            count++;
            token = strtok(NULL, " \n");
        }

        if (word_count + count > WORD_LIMIT) {
            send(sock, "Word limit exceeded. Session ended.\n", 37, 0);
            printf("Client exceeded word limit. Session closed.\n");
            break;
        } else {
            word_count += count;
            send(sock, "Message received.\n", 18, 0);
            printf("Client: %s\n", buffer);
            printf("Total words used: %d\n", word_count);

            if (word_count == WORD_LIMIT) {
                send(sock, "Word limit reached (25). Session ended.\n", 41, 0);
                printf("Limit reached. Closing session.\n");
                break;
            }
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main() {
    int sockfd;
    struct sockaddr_in saddr, caddr;
    socklen_t clen = sizeof(caddr);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        close(sockfd);
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept(sockfd, (struct sockaddr *)&caddr, &clen);
        if (*client_sock == -1) {
            perror("Accept failed");
            free(client_sock);
            continue;
        }

        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void *)client_sock) != 0) {
            perror("Thread creation failed");
            close(*client_sock);
            free(client_sock);
        }
        pthread_detach(tid);  // Clean up threads automatically
    }

    close(sockfd);
    return 0;
}

