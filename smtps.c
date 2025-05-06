#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2525  // SMTP typically runs on port 25 (use 2525 for testing)
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];

    // Send initial SMTP server greeting
    send(client_sock, "220 Simple SMTP Server Ready\r\n", 30, 0);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_sock, buffer, BUFFER_SIZE, 0);
        printf("Client: %s", buffer);

        if (strncmp(buffer, "HELO", 4) == 0) {
            send(client_sock, "250 Hello, pleased to meet you\r\n", 32, 0);
        } 
        else if (strncmp(buffer, "MAIL FROM:", 10) == 0) {
            send(client_sock, "250 Sender OK\r\n", 15, 0);
        } 
        else if (strncmp(buffer, "RCPT TO:", 8) == 0) {
            send(client_sock, "250 Recipient OK\r\n", 18, 0);
        } 
        else if (strncmp(buffer, "DATA", 4) == 0) {
            send(client_sock, "354 Start mail input; end with <CRLF>.<CRLF>\r\n", 45, 0);
        } 
        else if (strcmp(buffer, ".\r\n") == 0) {
            send(client_sock, "250 Message accepted\r\n", 22, 0);
        } 
        else if (strncmp(buffer, "QUIT", 4) == 0) {
            send(client_sock, "221 Goodbye\r\n", 13, 0);
            break;
        } 
        else {
            send(client_sock, "500 Command not recognized\r\n", 28, 0);
        }
    }
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create server socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for connections
    if (listen(server_sock, 5) < 0) {
        perror("Listening failed");
        exit(1);
    }

    printf("SMTP Server is running on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Client connected\n");
        handle_client(client_sock);
    }

    close(server_sock);
    return 0;
}
