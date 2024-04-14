#include <iostream>
#include <fstream>
#include <string>
#include <random_stuff.h>

using namespace std;

struct map {
    long long int ranges[3] = { 0 };
    //int range_start_source = 0;
    //int range_start_destination = 0;
    //int range_length = 0;
    long long int  offset = 0;
};

struct map_name {
    map map[1000];
    string name = "map name";
    int count = 0;
}map06[7], test;

long long int seeds[100];
int seeds_count = 0;

void assign_map_names() {
    map06[0].name = "seed-to-soil";
    map06[1].name = "soil-to-fertilizer";
    map06[2].name = "fertilizer-to-water";
    map06[3].name = "water-to-light";
    map06[4].name = "light-to-temperature";
    map06[5].name = "temperature-to-humidity";
    map06[6].name = "humidity-to-location";
}

void take_seeds(long long int *seed, string line) {

    string word_number;
    long long int number;
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
        cout << seeds[i] << ' ';
        seeds_count++;
    }
    cout << endl;
}

int index_w = 0;

int checkline(string line, int linecount) {

    if (line.empty())
        return -1;

    string word_number, word_string;
    long long int number;
    char current_char;

    int index = 0;
    int index_i = 0;
    current_char = line[index_i];

    //map* pointer = map06[0].map;

    for (index_i; index_i <= line.length(); index_i++) {

        current_char = line[index_i];

        if (index_i == line.length()) {
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
                for (int i = index_w; i< 7; i++) {
                    if (map06[i].name == word_string) {
                        cout << map06[i].name << endl;
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

int main()
{
    assign_map_names();
    
    string line;
    int game_pos = 0, sum = 0, linecount = 0, count = 0;

    ifstream myfile("example.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (count++ < 1)
                take_seeds(seeds, line);
            else {
                checkline(line, linecount++);
            }
            
            //lines[game_pos++] = line;
            //line_count++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    for (int i = 0; i < 7; i++) {
        cout << map06[i].name << ' ' << map06[i].count << endl;
        for (int y = 0; y < map06[i].count; y++) {
            cout << map06[i].map[y].ranges[0] << ' '; // range_start_source
            cout << map06[i].map[y].ranges[1] << ' '; // range_start_destination
            cout << map06[i].map[y].ranges[2] << ' '; // range_length
            cout << endl;
        }
        //cout << endl;
    }

    long long int range_start_source, range_start_destination, range_length, offset;
    long long int current_seed, min_seed = INT_MAX;

    for (int i = 0; i < seeds_count; i++) {
        current_seed = seeds[i];
        for (int y = 0; y < 7; y++) {
            for (int j = 0; j < map06[y].count; j++) {
                range_start_destination = map06[y].map[j].ranges[0]; //swapped
                range_start_source = map06[y].map[j].ranges[1]; // swapped
                range_length = map06[y].map[j].ranges[2];
                offset = abs(range_start_destination - range_start_source);
                if (current_seed >= range_start_source && current_seed < range_start_source + range_length) {
                    //current_seed += max(range_start_destination, range_start_source) - min(range_start_source, range_start_destination); // offset
                    if (range_start_destination > range_start_source) {
                        current_seed += offset;
                        break;
                    }
                    else if (range_start_destination < range_start_source) {
                        current_seed -= offset;
                        break;
                    }
                }
                //cout << current_seed << ' ';
            }
        }
        if (current_seed < min_seed)
            min_seed = current_seed;
        //cout << current_seed << endl;
    }
    cout << endl << min_seed << endl;
}