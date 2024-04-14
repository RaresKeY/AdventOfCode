#include <string>

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
long long int string_to_integer(std::string worded_number) {
    long long int number = 0;
    int wl = worded_number.length();
    for (int i = 0; i < wl; i++) {
        number += (worded_number[i] - '0') * pow(10, wl - i - 1); // transform string number to integer
    }
    return number;
}
bool is_digit(char digit) {
    if (digit >= '0' && digit <= '9')
        return true;
    return false;
}
int get_number(int line_index, int character_pos, std::string *lines) {
    int offset = 0, number_integer;
    std::string number;
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
int findsubstring(std::string substring, std::string mainstring, int startIndex = 0, int endIndex = -1) {
    if (endIndex != -1) {
        endIndex = mainstring.length();
    }
    int sl = substring.length(), pos;
    std::string substr = "";
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