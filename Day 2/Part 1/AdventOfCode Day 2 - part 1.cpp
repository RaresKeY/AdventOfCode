#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string w_list[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
string d_list[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
string c_list[3] = {"red", "green", "blue"};
int possible_list[3] = { 12, 13, 14 };
bool possible_check_list[3] = { 0, 0, 0 };

string RGB = "rgb";

struct ball {
    string color;
    int number;
} ball_list[3];


int findsubstring(string substring, string mainstring, int startIndex = 0, int endIndex = -1) {
    if (endIndex != -1) {
        endIndex = mainstring.length();
    }
    int sl = substring.length(), pos;
    string substr = "";
    for (int i = startIndex; i < endIndex - sl; i++){
        pos = i;
        for (int y = 0; y < sl; y++) {
            if (substring[y] != mainstring[i+y]) {
                pos = -1;
                break;
            }
        }
        if (pos != -1)
            return pos;
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

int string_to_integer(string worded_number) {
    int number = 0;
    int wl = worded_number.length();
    for (int i = 0; i < wl; i++) {
        number += (worded_number[i] - '0') * pow(10, wl - i -1); // transform string number to integer
    }
    return number;
}

int reuse_ballnumber_list[3] = { 0, 0, 0 };

bool checkline(string line, int game_expected_number) {

    string word_number;
    //char reuse_line_list[1000];
    reuse_ballnumber_list[0] = 0;
    reuse_ballnumber_list[1] = 0;
    reuse_ballnumber_list[2] = 0;
    int number = 0, game_number;
    char current_char;

    
    for (int i = 5; i < line.length(); i++) {
        // recognize the pattern of the information contained within the line
        //
        // we know that there will be the game number written as "Game #: " where # is 1,2,3...14...9230...etc
        // we know that there will the number of balls grabbed with their color matched as: "5 Red, 25 Green, 1 Blue" or "1 Red, 565 Green; 5 Green"
        // observation: there will be both numbers and digits to contend with
        // observation: you can create a string from an int
        // observation: finite, there is a finite number of numbers smaller than the given limits 12, 13, 14, given that there cannot be negative balls pulled out, 
        // if we look for these numbers, we only need to process number with less than or equal to 2 digits. detecting a number with more than 2 digits can directly elminate that game round.
        // observation: there is an empty space between each ball and their number
        // observation: there is a comma ',' between each number of balls pulled.
        // observation: there is a semicolon ';' between each hand of pulled balls.
        // observation: each game starts after a colon ':'
        // assumption: we assume the games are ordered

        // contingency: check for negative numbers in set
        // contingency: we check the game number with the indexer (ordered?)

        // solution
        // separate each hand clearly
        // identify the number of each color ball pulled, with a threshold of 3 digit numbers (BETTER IMPLEMENTED IF READ BACKWARDS)
        // compare to limit, if limit is exceeded, break loop
        //
        // how to read line and process it
        // we start after the colon ':'
        // we can use a reusable list for each hand, with the determination that the semicolon ';' is a reliable divider
        // after reading the hand into the list we process the list and then jump back to the start with the line indexer intact
        // the process: we find the words in the list: Red, Green & Blue, we read their accompanying number (to the left) and save it in a reusable list, 
        // we can jump out if there is a number with more than 2 digits.
        // 
        // finally we compare the numbers saved in the list with the limit numbers given and then sum up game number for the later result.
        // 
        // observation: we can reliably skip the first 5 character in the line: "Game "
        // observation: the words: Red, Green, Blue all star with a different letter,
        // that means we only need to check for the first letter to determine the ball color

        current_char = line[i];

        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
        }
        else if (current_char == ':') { // contingency: un-ordered games
            game_number = string_to_integer(word_number);
            word_number.clear();
            try {
                if (game_number != game_expected_number)
                    throw std::invalid_argument("Game Number outside prediction");
            }
            catch (std::invalid_argument& e)
            {
                cerr << e.what() << endl;
                return false;
            }
        }

        if (current_char >= 'a' && current_char <= 'z') { // check color by checking first letter (RGB)
            number = string_to_integer(word_number);
            word_number.clear();
            for (int z = 0; z < 3; z++) {
                if (current_char == RGB[z]) {
                    if (reuse_ballnumber_list[z] < number) {
                        reuse_ballnumber_list[z] = number;
                    }
                    if (number > possible_list[z]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
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

int main()
{
    int c, first = 0, last = 0, num,kolnum, sum = 0, index_m = 0;
    int pos_c, game_pos = 0;
    bool possible;
    string str;

    string line, word = "";
    ifstream myfile("example.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            game_pos++;
            c = checkline(line, game_pos);
            //cout << c << '\n';
            if (c) {
                //sum += game_pos;
            }
            sum += reuse_ballnumber_list[0] * reuse_ballnumber_list[1] * reuse_ballnumber_list[2];
        }
        myfile.close();

    }
    else cout << "Unable to open file";

    cout << "sum: " << sum;
}