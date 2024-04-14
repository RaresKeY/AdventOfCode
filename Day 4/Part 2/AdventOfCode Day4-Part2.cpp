#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int possible_list[3] = { 12, 13, 14 };
int line_count = 0;
bool possible_check_list[3] = { 0, 0, 0 };

string lines[10000];
int cards[10000] = { 0 };
int cards2[10000] = { 1 };

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

void sort_list(int* list, int L) { // seems inefficient, selection sort?
    int min_index = 0, temp;

    for (int i = 0; i < L; i++) {
        min_index = i;
        for (int j = i + 1; j < L; j++) {
            if (list[j] < list[min_index]) {
                min_index = j;
            }
        }
        temp = list[min_index];
        list[min_index] = list[i];
        list[i] = temp;
    }
}

void quick_sort(int* list, int i, int L) { // args: (ref list, start array, end array)
    int j = L, temp;

    while (j - i > 1) {
        if (list[i] < list[j]) {
            i++;
        }
        else if (list[i] > list[j]) {
            temp = list[i];
            list[i] = list[j - 1];
            list[j - 1] = list[j];
            list[j] = temp;
            j--;
        }
    }
    if (j > 0 && j - i > 1) { // left list array
        quick_sort(list, 0, j - 1);
    }
    if (L - j > 1) { // right list array
        quick_sort(list, j + 1, L);
    }
} //FIX

int ascending_order(const void* x, const void* y) {
    return (*(int*)y - *(int*)x);
}

int checkline(string line) {
    string word_number;
    int number;
    char current_char;

    int cards_own[1000], CL = 0;
    int numbers_win[1000], NL = 0;
    int* pointer = cards_own, * L_Pointer = &CL;
    int index = 0;
    int index_i = 0;
    current_char = line[index_i];
    while (line[index_i++] != ':') {
        //move index_i to start
    }

    for (index_i; index_i < line.length(); index_i++) {

        current_char = line[index_i];

        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
        }
        else if (current_char == '|') {
            pointer = numbers_win;
            L_Pointer = &NL;
            index = 0;
        }
        else { // check color by checking first letter (RGB)
            if (!word_number.empty()) {
                *L_Pointer = *L_Pointer + 1;
                number = string_to_integer(word_number);
                pointer[index++] = number;
                word_number.clear();
            }
        }
    }
    *L_Pointer = *L_Pointer + 1;
    number = string_to_integer(word_number);
    pointer[index++] = number;
    word_number.clear();

    std::cout << "CL = " << CL << ", ";
    std::cout << "NL = " << NL << endl;

    sort_list(cards_own, CL);
    sort_list(numbers_win, NL);

    std::cout << "cards_own" << '\n';
    for (int i = 0; i < CL; i++) {
        std::cout << cards_own[i] << ' ';
    }
    std::cout << endl;

    std::cout << "numbers_win" << '\n';
    for (int i = 0; i < NL; i++) {
        std::cout << numbers_win[i] << ' ';
    }
    std::cout << endl;

    int index_p1 = 0, index_p2 = 0, matches = 0, last_match = -1, c_count = 0;
    int max_L = (CL < NL) ? NL : CL;

    for (int i = 0; i < CL + NL - 1; i++) {
        if (cards_own[index_p1] == numbers_win[index_p2]) {
            if (cards_own[index_p1] != last_match) {
                matches++;
                last_match = cards_own[index_p1];
            }
            index_p2++;
        }
        if (cards_own[index_p1] < numbers_win[index_p2] && index_p1 < CL)
            index_p1++;
        if (cards_own[index_p1] > numbers_win[index_p2])
            index_p2++;
    }
    return matches;
}

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

double calc_matches(int matches) {
    if (matches == 0)
        return 0;
    else if (matches == 1)
        return 1;
    else
        return pow(2, matches - 1);
}

int main()
{
    int first = 0, last = 0, sum = 0, index_m = 0, game_pos = 0, matches;
    string str;

    string line, word = "";
    ifstream myfile("example.txt");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            matches = checkline(line);
            //cout << "matches: " << matches << endl;

            cards[game_pos] = matches;
            lines[game_pos++] = line;
            line_count++;
        }
        myfile.close();

    }
    else std::cout << "Unable to open file";

    //calculate for part 2

    for (int i = 0; i < line_count; i++) {
        cards2[i] = 1;
    }

    for (int i = 0; i < line_count; i++) {
        for (int y = i; y < cards[i] + i; y++) {
            cards2[y + 1] += 1 * cards2[i];
        }
    }

    sum = 1;
    for (int i = 1; i < line_count; i++) {
        sum += cards2[i];
    }

    std::cout << "sum: " << sum;
}