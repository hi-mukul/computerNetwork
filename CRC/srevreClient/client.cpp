#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 9000
#define MAX 1024

string divide(string dividend, string divisor)
{
    int n = divisor.size();
    string temp = dividend;
    temp.append(n - 1, '0');
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
    string crc = temp.substr(temp.size() - (n - 1));
    return dividend + crc;
}

int main()
{
    int sockfd;
    struct sockaddr_in serveraddr;
    char buffer[MAX];

    string data = "1101011011";
    string divisor = "10011";
    string encoded = divide(data, divisor);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    string message = encoded + "|" + divisor;
    send(sockfd, message.c_str(), message.length(), 0);

    int n = read(sockfd, buffer, MAX);
    buffer[n] = '\0';

    cout << "Server says: " << buffer << endl;

    close(sockfd);
    return 0;
}
