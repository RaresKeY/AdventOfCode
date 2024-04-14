#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string w_list[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
string d_list[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
string c_list[3] = { "red", "green", "blue" };
int possible_list[3] = { 12, 13, 14 };
int line_count = 0;
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
    for (int i = startIndex; i < endIndex - sl; i++) {
        pos = i;
        for (int y = 0; y < sl; y++) {
            if (substring[y] != mainstring[i + y]) {
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
        number += (worded_number[i] - '0') * pow(10, wl - i - 1); // transform string number to integer
    }
    return number;
}

int reuse_ballnumber_list[3] = { 0, 0, 0 };

struct number_pos {
    int pos_start = -1;
    int length = 0;
    int line;
    string number;
}number_in_list[1000];

int symbol_pos[500];

string lines[10000];

bool checkline(string line, int game_expected_number) {

    string word_number;
    int number;
    string list_numbers;
    int count = 0;
    int count_symbols = 0;

    //char reuse_line_list[1000];
    reuse_ballnumber_list[0] = 0;
    reuse_ballnumber_list[1] = 0;
    reuse_ballnumber_list[2] = 0;
    int game_number;
    char current_char;



    for (int i = 0; i < line.length(); i++) {
        
        current_char = line[i];

        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
            number_in_list[count].length++;
        }
        else if (current_char == '.') {
            number_in_list[count].pos_start = i - number_in_list[count].length - 1;
            number_in_list[count].number = word_number;
            count++;
        }
        else {
            symbol_pos[count_symbols++];
        }

        if (current_char >= 'a' && current_char <= 'z') { // check color by checking first letter (RGB)
            number = string_to_integer(word_number);
            word_number.clear();
            for (int z = 0; z < 3; z++) {
                if (current_char == RGB[z]) {
                    if (reuse_ballnumber_list[z] < number) {
                        reuse_ballnumber_list[z] = number;
                    }
                    /*
                    if (number > possible_list[z]) {
                        return false;
                    }
                    */
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
/*
int check_next_line(int game_pos, int symbol_pos) {
    int sum = 0, number_pos;
    string word_number;
    char current_char;

    for (int i = 0; i < lines[game_pos].length(); i++) {
        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
        }
        else if (!word_number.empty()) {
            number_pos = i - 1 - word_number.length();
            if (number_pos >= symbol_pos - 1 && number_pos <= symbol_pos + 1) {
                sum += string_to_integer(word_number);
            }
        }
    }

    return sum;
}
*/
bool is_digit(char digit) {
    if (digit >= '0' && digit <= '9')
        return true;
    return false;
}

int get_number(int line_index, int character_pos) {
    int offset = 0, number_integer;
    string number;
    while (is_digit(lines[line_index][character_pos + offset])) {
        offset--;
        if (character_pos + offset < 0) {
            break;
        }
    }
    offset++;
    while (is_digit(lines[line_index][character_pos + offset])) {
        number += lines[line_index][character_pos + offset];
        offset++;
    }

    number_integer = string_to_integer(number);

    return number_integer;
}

bool detected_digits[3][3] = { false };

bool detected_touches(int i, int y) {
    if (y > 0)
        if (detected_digits[i][y - 1]) // digit detected left side
            return true;
    if (y < 2)
        if (detected_digits[i][y + 1]) // digit detected right side
            return true;

    return false; // no digit detected within edge limits
}

int get_gears_number() {
    int check = 2, count = 0;

    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 3; y++) {
            if (detected_digits[i][y] == true) {
                if (check == 2) {
                    count++;
                    check = 0;
                }
                if (check < 2)
                    check++;
            }
        }
    }

    return count;
}

int numbers[2];

int check_around_symbol(int line_index, int character_pos) {

    int sum = 0, i_start = -1, i_end = 1, count = 0;
    if (line_index == line_count)
        i_end = 0;
    else if (line_index == 0)
        i_start = 0;

    for (int i = i_start; i <= i_end; i++) {
        for (int y = -1; y <= 1; y++) {
            if (character_pos + y >= 0 && character_pos < lines[line_index + 1].length()) { // if it is within string outer limits
                if (is_digit(lines[line_index + i][character_pos + y])) {
                    detected_digits[i + 1][y + 1] = true;
                    if (!detected_touches(i + 1, y + 1)) {
                        if (lines[line_index][character_pos] == '*'){
                            if (count < 2) {
                                //sum += get_number(line_index + i, character_pos + y);
                                numbers[count++] = get_number(line_index + i, character_pos + y);
                            }
                            else
                                goto jump1;
                        }
                    }
                }
            }
        }
    }
    jump1:

    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 3; y++) {
            detected_digits[i][y] = false;
        }
    }

    if (count != 2) {
        return 0;
    }

    cout << numbers[0] << ' ' << numbers[1] << '\n';
    return numbers[0] * numbers[1];

}


int Array_test[3] = { -1, 0, 1, };

int go_through_lines() {
    char current_char;
    int sum = 0;

    for (int i = 0; i < line_count; i++) {
        for (int y = 0; y < lines[i].length(); y++) {
            current_char = lines[i][y];

            if (!is_digit(current_char) && current_char == '*') { // is symbol?
                sum += check_around_symbol(i, y);
            }
        }
    }
    return sum;
}

int main()
{
    int c, first = 0, last = 0, num, kolnum, sum = 0, index_m = 0;
    int pos_c, game_pos = 0;
    bool possible;
    string str;

    string line, word = "";
    ifstream myfile("example.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines[game_pos++] = line;
            line_count++;
            //cout << c << '\n';
            //if (c) {
                //sum += game_pos;
            //}
            //cout << reuse_ballnumber_list[0] << ' ' << reuse_ballnumber_list[1] << ' ' << reuse_ballnumber_list[2] << '\n';
            //sum += reuse_ballnumber_list[0] * reuse_ballnumber_list[1] * reuse_ballnumber_list[2];
        }
        myfile.close();

    }
    else cout << "Unable to open file";

    sum = go_through_lines();

    cout << "sum: " << sum;
}