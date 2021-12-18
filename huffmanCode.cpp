#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int chars_count[50];

int dataInput()
{
    int count = 0;
    fstream f("input.txt", ios::in);
    if (f.is_open())
    {
        char ch;
        while (f >> ch)
        {
            count++;
            if (ch >= 'a' and ch <= 'z')
                chars_count[ch]++;
            else
                chars_count[0]++;
        }
    }
    f.close();
    return count;
}

int main()
{
    cout << "Hello,world!" << endl;

    return 0;
}