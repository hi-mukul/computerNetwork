#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define port 9000
#define max 1024

void send_file(FILE *fp, int sockfd)
{
    // FILE *fp;

    char *filename = "temp.txt";
    fp = fopen(filename, "r");
    char buff[max] = {0};

    while (fgets(buff, max, fp) != NULL)
    {
        send(sockfd, buff, max, 0);
        bzero(buff, max);
    }
}

int main()
{
    struct sockaddr_in serveraddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //    if(sockfd==-1) {
    //       printf("socket creation error\n");
    //       exit(0);
    //    }
    //    printf("socket creation successful\n");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(port);

    connect(sockfd, (SA *)&serveraddr, sizeof(serveraddr));

    send_file(fp, sockfd);

    close(sockfd);
}