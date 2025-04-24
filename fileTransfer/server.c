#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define port 9000
#define max 1024

void write_file(int connfd)
{
    FILE *fp;
    char *filename = "receive.txt";
    char buff[max];
    fp = fopen(filename, "w");

    while (1)
    {
        int bytes = recv(connfd, buff, max, 0);
        if (bytes <= 0)
            return;
        fprintf(fp, "%s", buff);
        bzero(buff, max);
    }
}

int main()
{
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd, connfd, len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd, (SA *)&serveraddr, sizeof(serveraddr));

    listen(sockfd, 5);

    len = sizeof(clientaddr);
    connfd = accept(sockfd, (SA *)&clientaddr, &len);

    write_file(connfd);
    close(connfd);
}