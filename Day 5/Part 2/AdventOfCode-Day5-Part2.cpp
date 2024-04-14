#include <iostream>
#include <fstream>
#include <string>
#include <random_stuff.h>
#include <Unit_Tests.h>

//template void sort_list<map>(map* list, int L, bool (*compare)(map, map));

const int SEED_NUMBER = 300;

map_name map06[7], test;

int64_t seeds[SEED_NUMBER];
range seed_maps[SEED_NUMBER];
int seed_maps_length = 0;
int map_ranges_length = 0;
int index_w = 0;
int seeds_count = 0;

// has debug value?
void assign_map_names() {
    map06[0].name = "seed-to-soil";
    map06[1].name = "soil-to-fertilizer";
    map06[2].name = "fertilizer-to-water";
    map06[3].name = "water-to-light";
    map06[4].name = "light-to-temperature";
    map06[5].name = "temperature-to-humidity";
    map06[6].name = "humidity-to-location";
}
// dirty way to read initial seeds
void take_seeds(int64_t* seed, std::string line) {

    std::string word_number;
    int64_t number;
    int index = 0, index_i = 0;
    char current_char;

    while (line[index_i++] != ':') {
        //move index_i to start of desired line input
    }

    for (index_i; index_i < line.length(); index_i++) {
        current_char = line[index_i];
        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
        }
        else {
            if (!word_number.empty()) {
                number = string_to_integer(word_number);
                seeds[index++] = number;
                word_number.clear();
            }
        }
    }
    number = string_to_integer(word_number);
    seeds[index] = number;
    word_number.clear();

    for (int i = 0; i < index + 1; i++) {
        //std::cout << seeds[i] << ' ';
        seeds_count++;
    }
    //std::cout << endl;
    seeds_count /= 2;

    //second part, change in seeds input
    int second_index = 0;
    for (int i = 0; i < seeds_count; i++) {
        seed_maps[i] = { seeds[i*2], seeds[i*2 + 1] };
    }

    seed_maps_length = seeds_count;

    return;
}
// dirty way to read range map
int checkline(std::string line, int linecount) {

    if (line.empty())
        return -1;

    std::string word_number, word_string;
    int64_t number;
    char current_char;

    int index = 0;
    int index_i = 0;
    current_char = line[index_i];

    //map* pointer = map06[0].map;

    size_t line_length = line.length();

    for (index_i; index_i <= line_length; index_i++) {

        current_char = line[index_i];

        if (index_i == line_length) {
            goto jump1;
        }
        if (current_char >= '0' && current_char <= '9') { // get number
            word_number += current_char;
        }
        else if ((current_char >= 'a' && current_char <= 'z') || current_char == '-') {
            word_string += current_char;
        }
        else {
        jump1:
            if (!word_number.empty()) {
                number = string_to_integer(word_number);
                map06[index_w].map[map06[index_w].count].ranges[index++] = number;
                word_number.clear();
                if (index == 3)
                    map06[index_w].count++;
            }
            else if (!word_string.empty()) {
                for (int i = index_w; i < 7; i++) {
                    if (map06[i].name == word_string) {
                        //std::cout << map06[i].name << std::endl;
                        index_w = i;
                        return 0;
                    }
                }
                word_string.clear();
            }
        }
    }
    return 1;
}
// splits maps based on mapped ranges
void split_range_ins(range* seed_maps, range range_small, int* seed_maps_length) {

    int64_t end_index_map, end_index_small = range_small.index_S + range_small.length;
    int64_t mid_point_left, mid_point_right, left_most_index, right_most_index;
    range temp_range[3] = { 0, 0 };
    int temp_range_length = 0;

    for (int i = *seed_maps_length - 1; i >= 0; i--) {
        end_index_map = seed_maps[i].index_S + seed_maps[i].length;

        // if second range NOT outside first range
        if (!(range_small.index_S > end_index_map || end_index_small < seed_maps[i].index_S)) {
            // five possible cases: {[]} inside, [{}] outside, [] overlap, [{]} left, {[}] right.

            mid_point_left = std::max(range_small.index_S, seed_maps[i].index_S);  // within map range
            mid_point_right = std::min(end_index_small, end_index_map);            // within map range
            left_most_index = seed_maps[i].index_S;                      //  leftmost within map range
            right_most_index = end_index_map;                            // rightmost within map range

            // split in max 3 new ranges
            temp_range[0] = { left_most_index, mid_point_left - left_most_index };
            temp_range[1] = { mid_point_left, mid_point_right - mid_point_left };
            temp_range[2] = { mid_point_right, right_most_index - mid_point_right };

            // replace range at index i with range at index length-1 and remove 1 from length
            seed_maps[i] = seed_maps[-- * seed_maps_length];

            // add ranges that have length > 0
            for (int y = 0; y < 3; y++) {
                if (temp_range[y].length > 0) {
                    seed_maps[*seed_maps_length] = temp_range[y];
                    *seed_maps_length += 1;
                }
            }
        }
    }
}
// thing that is broken?
void thing() {
    int64_t range_start_source, range_start_destination, range_length, offset, min_seed = INT64_MAX;
    range temp_offset_ranges[SEED_NUMBER] = {0, 0};
    int temp_offset_ranges_length = 0;

    for (int y = 0; y < 7; y++) { // for every conversion type (7 types)

        for (int j = 0; j < map06[y].count; j++) { // for every listed range of conversion in current conversion type

            range_start_source = map06[y].map[j].ranges[1]; // swapped
            range_start_destination = map06[y].map[j].ranges[0]; // swapped
            range_length = map06[y].map[j].ranges[2];

            range current_map_range = { range_start_source, range_length };
            offset = offset_particular(range_start_destination, range_start_source); // offset

            // should splits all the ranges correctly
            if (seed_maps_length > 0) {
                split_range_ins(seed_maps, { range_start_source, range_length }, &seed_maps_length);
            }
            
            // move offset ranges to temporary list
            for (int z = seed_maps_length - 1; z >= 0; z--){ // z >= seed_maps_length -4
                // if range is within mapped range (we split it previously to fit)
                if (seed_maps[z].index_S >= range_start_source &&  seed_maps[z].index_S + seed_maps[z].length <= range_start_source + range_length) {
                    temp_offset_ranges[temp_offset_ranges_length++] = seed_maps[z];
                    temp_offset_ranges[temp_offset_ranges_length - 1].index_S += offset;
                    seed_maps[z] = seed_maps[--seed_maps_length]; // forgot to move found seed to last before removing length index, this was the problem
                    std::cout << seed_maps_length << '\n';
                }
            }
        }
        // move offset ranges back into main list for next conversion type loop
        for (int z = 0; z < temp_offset_ranges_length; z++) {
            seed_maps[seed_maps_length++] = temp_offset_ranges[z];
        }
        temp_offset_ranges_length = 0;
    }
}
bool compare_map_specific_source(map x, map y) {
    return x.ranges[1] < y.ranges[1];
}
int main()
{
    // test stuff
    convert_test_ranges_ins();
    //display_test_range();
    test_run_small(&split_range_ins);

    assign_map_names();

    std::string line;
    int game_pos = 0, sum = 0, linecount = 0, count = 0;

    std::ifstream myfile("example.txt");

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            if (count++ < 1)
                take_seeds(seeds, line);
            else {
                checkline(line, linecount++);
            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";

    int64_t min_seed = INT64_MAX;

    // sort by source value (ranges[1])
    for (int i = 0; i < 7; i++) {
        sort_list<map>(map06[i].map, map06[i].count, &compare_map_specific_source);
    }

    // Verify the sorting (printing ranges[1])
    for (int i = 0; i < 7; i++) {
        std::cout << "map06[" << i << "] sorted ranges[1]: \n";
        for (int j = 0; j < map06[i].count; ++j) {
            std::cout << map06[i].map[j].ranges[1] << "\n";
        }
        std::cout << std::endl;
    }

    thing(); // this broken

    for (int i = 0; i < seed_maps_length; i++) {
        if (seed_maps[i].index_S < min_seed)
            min_seed = seed_maps[i].index_S;
    }

    std::cout << std::endl << min_seed << std::endl;
}

