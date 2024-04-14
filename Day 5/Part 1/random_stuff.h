#pragma once

#ifndef RANDOM_STUFF_H
#define RANDOM_STUFF_H

#include <string>

void sort_list(int* list, int L);
long long int string_to_integer(std::string worded_number);
bool is_digit(char digit);
int get_number(int line_index, int character_pos);
int findsubstring(std::string substring, std::string mainstring, int startIndex = 0, int endIndex = -1);

#endif

