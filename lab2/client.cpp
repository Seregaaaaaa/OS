#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket creation error\n");
        exit(EXIT_FAILURE);
    }

    
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Connection Failed \n");
        return -1;
    }

    
    const char* message = "Hello, my name is Sergei!";
    send(sock, message, strlen(message), 0);
    printf("Message sent\n");

    close(sock);
    return 0;
}