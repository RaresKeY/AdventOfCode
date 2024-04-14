#include <string>

struct map {
    int64_t ranges[3] = { 0 };
};
struct map_name {
    map map[1000];
    std::string name = "map name";
    int count = 0;
};
struct range {
    int64_t index_S;
    int64_t length;
};

template <typename T> void sort_list(T* list, int L, bool (*compare)(T, T)) {
    int min_index = 0;
    T temp;

    for (int i = 0; i < L; i++) {
        min_index = i;
        for (int j = i + 1; j < L; j++) {
            if (compare(list[j], list[min_index])) {
                min_index = j;
            }
        }
        temp = list[min_index];
        list[min_index] = list[i];
        list[i] = temp;
    }
}

int64_t string_to_integer(std::string worded_number) {
    int64_t number = 0;
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
int64_t get_number(int line_index, int character_pos, std::string *lines) {
    int offset = 0;
    int64_t number_integer;
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
int findsubstring(std::string substring, std::string mainstring, int startIndex = 0, size_t endIndex = -1) {
    if (endIndex != -1) {
        endIndex = mainstring.length();
    }
    size_t sl = substring.length();
    int pos;
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
    return -1;
}
int64_t offset_particular(int64_t range_start_destination, int64_t range_start_source) {

    int64_t offset = abs(range_start_destination - range_start_source);

    if (range_start_source > range_start_destination)
        offset = -offset;

    return offset;
}

template void sort_list<map>(map* list, int L, bool (*compare)(map, map));