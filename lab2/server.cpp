#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

const int port = 8080;
const int backlog = 5;

volatile sig_atomic_t wasSigHup = 0;

void sigHupHandler(int sigNumber) {
    wasSigHup = 1;
}

int main() {
    int server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    /*
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    */

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }


    if (listen(server_socket, backlog) == -1) {
        perror("Listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server started on port %d\n", port);


    struct sigaction sa;
    sigaction(SIGHUP, NULL, &sa);
    sa.sa_handler = sigHupHandler;
    sa.sa_flags |= SA_RESTART;
    sigaction(SIGHUP, &sa, NULL);


    sigset_t blocked_mask, orig_mask;
    sigemptyset(&blocked_mask);
    sigaddset(&blocked_mask, SIGHUP);
    sigprocmask(SIG_BLOCK, &blocked_mask, &orig_mask);

    int client_socket = 0;

    while (true) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        
        if (client_socket > 0) {
            FD_SET(client_socket, &read_fds);
        }

        int max_sd = (client_socket > server_socket) ? client_socket : server_socket;

        if (pselect(max_sd + 1, &read_fds, NULL, NULL, NULL, &orig_mask) == -1) {
            if (errno == EINTR) {
                if (wasSigHup == 1) {
                    printf("SIGHUP received.\n");
                    wasSigHup = 0;
                }
                continue;
            } else {
                perror("pselect error");
                close(server_socket);
                if (client_socket > 0) {
                    close(client_socket);
                }
                exit(EXIT_FAILURE);
            }
        }


        if (FD_ISSET(server_socket, &read_fds)) {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
            if (client_socket == -1) {
                perror("Accept error");
                continue;
            }
            printf("New connection.\n");
        }


        if (client_socket > 0 && FD_ISSET(client_socket, &read_fds)) {
            char buffer[1024] = {0};
            int read_bytes = read(client_socket, buffer, sizeof(buffer));
            if (read_bytes > 0) {
                printf("Received data: %d bytes\n", read_bytes);
                printf("Message: %s\n", buffer);
            } else if (read_bytes == 0) {
                printf("Client disconnected.\n");
                close(client_socket);
                client_socket = 0;
            } else {
                perror("Read error");
                close(client_socket);
                client_socket = 0;
            }
        }
    }

    close(server_socket);
    return 0;
}