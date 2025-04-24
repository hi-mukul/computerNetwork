#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 9000
#define MAX 1024

string verify(string data, string divisor)
{
    int n = divisor.size();
    string temp = data;
    for (int i = 0; i < temp.size() - n + 1; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < n; j++)
            {
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }
    return temp.substr(temp.size() - (n - 1));
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char buffer[MAX];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 5);

    cout << "Server listening on port " << PORT << "...\n";

    connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
    int n = read(connfd, buffer, MAX);
    buffer[n] = '\0';

    string received(buffer);
    size_t sep = received.find('|');
    string data = received.substr(0, sep);
    string divisor = received.substr(sep + 1);

    string rem = verify(data, divisor);
    bool error = false;
    for (char c : rem)
    {
        if (c == '1')
        {
            error = true;
            break;
        }
    }

    string response = error ? "Error detected in transmission" : "Data received correctly";
    send(connfd, response.c_str(), response.length(), 0);

    close(connfd);
    close(sockfd);
    return 0;
}
