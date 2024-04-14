#pragma once

#ifndef RANDOM_STUFF_H
#define RANDOM_STUFF_H

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

template <typename T> void sort_list(T* list, int L, bool (*compare)(T, T));

int64_t string_to_integer(std::string worded_number);
bool is_digit(char digit);
int64_t get_number(int line_index, int character_pos, std::string* lines);
int findsubstring(std::string substring, std::string mainstring, int startIndex = 0, size_t endIndex = -1);
int64_t offset_particular(int64_t range_start_destination, int64_t range_start_source);

#endif

