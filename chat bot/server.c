#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define max 80
#define port 8000
#define SA struct sockaddr

void func(int connfd)
{
    char buff[max];
    int i;

    for (;;)
    {
        bzero(buff, max);
        read(connfd, buff, max);
        printf("mesage form client: %s", buff);

        bzero(buff, max);
        printf("enter message\n");
        i = 0;
        while ((buff[i++] = getchar()) != '\n')
            ;
        write(connfd, buff, max);
    }
}

int main()
{
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd, connfd, len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);

    bind(sockfd, (SA *)&serveraddr, sizeof(serveraddr));

    listen(sockfd, 5);

    len = sizeof(clientaddr);
    connfd = accept(sockfd, (SA *)&clientaddr, &len);

    func(connfd);
    close(connfd);
}