#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>  
#include <process.h>   
#include "lib/file_helper.h"
#include "lib/http_helper.h"

#define PORT 9090
#define BUFFER_SIZE 4096

void handle_client(void *socket_desc);

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server, client;
    int client_size;

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    // create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        return 1;
    }
    // server configuration
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    listen(server_fd, 3);
    printf("Server running on port %d...\n", PORT);

   // accept and handle client connections in seperated threads
    while (1) {
        client_size = sizeof(client);
        client_fd = accept(server_fd, (struct sockaddr *)&client, &client_size);
        if (client_fd == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;
        }
        printf("Client connected...\n");

        _beginthread(handle_client, 0, (void *)client_fd);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}

void handle_client(void *socket_desc) {
    SOCKET client_fd = (SOCKET)socket_desc;
    char buffer[BUFFER_SIZE];
    int recv_size;
     
   // Read client http requests
    recv_size = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (recv_size > 0) {
        buffer[recv_size] = '\0';
        printf("Received Request:\n%s\n", buffer);

        char file_name[50] = "index.html"; 

        // Extract the requested file name from the request
        sscanf(buffer, "GET /%49s ", file_name);
        if (strcmp(file_name, "/") == 0 || strcmp(file_name, "") == 0) {
            strcpy(file_name, "index.html");
        }

        //  Find & Serve the Requested File by Constructing full file path
        char file_path[100];
        snprintf(file_path, sizeof(file_path), "src\\%s", file_name);

        long file_size;
        int file_fd = get_file_descriptor(file_path, &file_size);
        
        if (file_fd < 0) {
            // File not found, redirect to 404.html
            char redirect_path[100];
            snprintf(redirect_path, sizeof(redirect_path), "src\\404.html");

            int redirect_fd = get_file_descriptor(redirect_path, &file_size);
            if (redirect_fd < 0) {
                // If 404.html is also not found, send a simple 404 response
                send(client_fd, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", 47, 0);
            } else {
                // Send a 302 Found redirect response
                const char *mime = get_mime_type(get_file_extension("404.html"));
                char response_header[BUFFER_SIZE];
                
                snprintf(response_header, BUFFER_SIZE,
                    "HTTP/1.1 302 Found\r\n"
                    "Location: /404.html\r\n"
                    "Content-Type: %s\r\n"
                    "Content-Length: %ld\r\n"
                    "Connection: close\r\n\r\n",
                    mime, file_size);
                
                printf("Sending Response:\n%s\n", response_header);
                send(client_fd, response_header, strlen(response_header), 0);
                send_file(client_fd, redirect_fd);
            }
            } else {
            // Send the Requested File
            const char *mime = get_mime_type(get_file_extension(file_name));
            char response_header[BUFFER_SIZE];
        
            snprintf(response_header, BUFFER_SIZE,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %ld\r\n"
                "Connection: close\r\n\r\n",  
                mime, file_size);
            
            printf("Sending Response:\n%s\n", response_header);
            send(client_fd, response_header, strlen(response_header), 0);
            send_file(client_fd, file_fd);
        }   
        
    }

    closesocket(client_fd);
}



