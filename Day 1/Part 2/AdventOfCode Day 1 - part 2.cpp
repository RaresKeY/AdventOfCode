#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string w_list[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
string d_list[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

int findsubstring(string substring, string mainstring) {
    int ml = mainstring.length(), sl = substring.length();
    string substr = "";
    for (int i = 0; i < ml - sl; i++){
        substr = mainstring.substr(i, i + sl);
        if (substring == substr)
            return true;
    }
}

int first_number(string n) {
    int In = INT_MAX, i, r;
    for (int y = 0; y < 10; y++)
    {
        i = n.find(w_list[y]);
        if (i != -1)
            if (i < In) {
                In = i;
                r = y;
            }
    }
    for (int y = 0; y < 10; y++)
    {
        i = n.find(d_list[y]);
        if (i != -1)
            if (i < In) {
                In = i;
                r = y;
            }
    }
    if (In != INT_MAX)
        return r;

    return -1;
}

int last_number(string n) {
    int In = -1, i, r;
    for (int y = 0; y < 10; y++)
    {
        i = n.rfind(w_list[y]);
        if (i > In) {
            In = i;
            r = y;
        }
    }
    for (int y = 0; y < 10; y++)
    {
        i = n.rfind(d_list[y]);
        if (i > In) {
            In = i;
            r = y;
        }
    }
    if (In != -1)
        return r;

    return -1;
}

void main()
{
    int c, first = 0, last = 0, num,kolnum, sum = 0;
    string str;

    string line, word = "";
    ifstream myfile("example.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            num = 0;

            first = first_number(line);
            if (first != -1) {
                last = last_number(line);
                num = (first * 10) + last;
                sum += num;
                //cout << num << '\n';
            }
        }
        myfile.close();

    }
    else cout << "Unable to open file";

    cout << "sum: " << sum;
}