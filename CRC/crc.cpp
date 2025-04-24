#include <iostream>
#include <string>
using namespace std;

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
                if (temp[i + j] == divisor[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }
    string crc = temp.substr(temp.size() - (n + 1));
    cout << crc << endl;
    return dividend + crc;
}

string verify(string code, string divisor)
{
    int n = divisor.size();
    string temp = code;

    for (int i = 0; i < temp.size() - n + 1; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < n; j++)
            {
                if (temp[i + j] == divisor[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }
    return temp;
}

int main()
{
    string dividend = "1101011011";
    string divisor = "10011";

    string code = divide(dividend, divisor);
    cout << "Encoded message: " << code << endl;

    string check = verify(code, divisor);
    cout << "Remainder after verification: " << check << endl;

    return 0;
}