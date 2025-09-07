// networking/imports + live demo (send typed text)
// beacon.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

int main(void) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
#endif

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); return 1; }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
#ifdef _WIN32
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) != 1) { perror("inet_pton"); return 1; }
#endif

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect");
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        return 1;
    }

    char buf[256];
    printf("Type a message: ");
    if (!fgets(buf, sizeof(buf), stdin)) buf[0] = '\0';

    send(sockfd, buf, (int)strlen(buf), 0);

#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif
    puts("Message sent.");
    return 0;
}
