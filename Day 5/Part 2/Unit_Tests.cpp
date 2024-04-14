#include <string>
#include <random_stuff.h>
#include <iostream>

struct test_ranges {
    range map_range = { 0, 0 };
    range small_range = { 0, 0 };
};

map_name test_map;

const int TEST_LENGTH = 9;
int length_test = TEST_LENGTH;

test_ranges small_data_set_converted[TEST_LENGTH];

range small_data_set_ready[TEST_LENGTH * 10];

//{[]} inside, [{}] outside, [] overlap, [{]} left, {[}] right.
test_ranges small_data_set[TEST_LENGTH] = {
    { {10, 20}, {11, 19} }, // {[]} inside
    { {10, 20}, {10, 19} }, // {[]} inside + overlap left
    { {10, 20}, {11, 20} }, // {[]} inside + overlap right
    { {10, 20}, { 9, 21} }, // [{}] outside
    { {10, 20}, {10, 21} }, // [{}] outside + overlap left ALSO {[}] right + overlap left
    { {10, 20}, { 9, 20} }, // [{}] outside + overlap right ALSO [{]} left + overlap right
    { {10, 20}, {10, 20} }, //  [] overlap
    { {10, 20}, { 0, 15} }, // [{]} left
    { {10, 20}, {15, 30} }, // {[}] right
};


void display_test_range() {
    for (int i = 0; i < TEST_LENGTH; i++) {
        std::cout << small_data_set_converted[i].small_range.index_S << ' ' << small_data_set_converted[i].small_range.length << '\n';
    }
}
void convert_test_ranges_ins() {
    for (int i = 0; i < TEST_LENGTH; i++) {
        small_data_set_converted[i] = small_data_set[i];
        small_data_set_converted[i] = small_data_set[i];

        small_data_set_converted[i].map_range.length = small_data_set[i].map_range.length - small_data_set[i].map_range.index_S;
        small_data_set_converted[i].small_range.length = small_data_set[i].small_range.length - small_data_set[i].small_range.index_S;
    }

    for (int i = 0; i < TEST_LENGTH; i++) {
        small_data_set_ready[i] = small_data_set_converted[i].map_range;
    }
}
bool test_run_small(void (*test_funct)(range*, range, int*)) {
    for (int i = 0; i < length_test; i++) {
        test_funct(small_data_set_ready, small_data_set_converted[i].small_range, &length_test);
    }

    std::cout << "\nFinished: (" << length_test << ")" << '\n';
    for (int i = 0; i < length_test; i++) {
        std::cout << small_data_set_ready[i].index_S << ' ' << small_data_set_ready[i].length << '\n';
    }
    return true;
}