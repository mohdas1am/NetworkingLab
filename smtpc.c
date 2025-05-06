/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // IP of your SMTP server (localhost for WSL)
#define PORT 2525              // Port number (must match server)
#define BUFFER_SIZE 1024

void send_command(int sock, const char *command) {
    printf("C: %s", command); // Log command
    send(sock, command, strlen(command), 0);

    char buffer[BUFFER_SIZE] = {0};
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer); // Log server response
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to SMTP server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // Read server greeting
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer);

    // SMTP commands
    send_command(sock, "HELO example.com\r\n");
    send_command(sock, "MAIL FROM:<your_email@example.com>\r\n");
    send_command(sock, "RCPT TO:<recipient@example.com>\r\n");
    send_command(sock, "DATA\r\n");

    // Send full email body with proper ending
    const char *email_body =
        "Subject: Test Email\r\n"
        "\r\n"
        "Hello, this is a test email from C socket program.\r\n"
        ".\r\n";

    printf("C: %s", email_body);  // Log entire body
    send(sock, email_body, strlen(email_body), 0);

    // Receive response to message
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer);

    // Send QUIT command
    send_command(sock, "QUIT\r\n");

    // Close socket
    close(sock);
    printf("Email sent successfully.\n");

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2525
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

void send_command(int sock, const char *command) {
    printf("C: %s", command); // Log command
    send(sock, command, strlen(command), 0);

    char buffer[BUFFER_SIZE] = {0};
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer); // Log server response
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to SMTP server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // Read server greeting
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("S: %s", buffer);

    // SMTP conversation
    send_command(sock, "HELO localhost\r\n");
    send_command(sock, "MAIL FROM:<sender@example.com>\r\n");
    send_command(sock, "RCPT TO:<receiver@example.com>\r\n");
    send_command(sock, "DATA\r\n");
    send_command(sock, "Subject: Test Mail\r\n");
    send_command(sock, "This is a test message.\r\n");
    send_command(sock, ".\r\n");
    send_command(sock, "QUIT\r\n");

    close(sock);
    return 0;
}

