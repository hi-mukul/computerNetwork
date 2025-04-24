#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define max 80
#define port 8000
#define SA struct sockaddr

void sendMess(int sockfd)
{
    char buff[max];
    int i;

    while (1)
    {
        bzero(buff, max);
        printf("enter message\n");
        i = 0;
        while ((buff[i++] = getchar()) != '\n')
            ;
        write(sockfd, buff, max);

        bzero(buff, max);
        read(sockfd, buff, max);
        printf("mesage form server: %s", buff);
    }
}

int main()
{
    struct sockaddr_in serveraddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(port);

    connect(sockfd, (SA *)&serveraddr, sizeof(serveraddr));

    sendMess(sockfd);
    close(sockfd);
}