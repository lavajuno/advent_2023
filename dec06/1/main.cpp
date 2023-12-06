/*
 * December 6, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <vector>
#include <filereader.hpp>

std::vector<uint> readUints(std::string& line) {
    std::stringstream words(line);
    std::string word;
    std::vector<uint> values({});

    words >> word; // "Time:" or "Distance:"
    while(!words.eof()) {
        words >> word;
        values.push_back(stoi(word));
    }
    return values;
}

std::pair<uint, uint> getBounds(uint time, uint distance) {
    double d_time = (double) time;
    double d_distance = (double) distance;
    double n0 = 1 * d_time - sqrt(pow(d_time, 2) - 4 * d_distance);
    double n1 = 1 * d_time + sqrt(pow(d_time, 2) - 4 * d_distance);
    uint lower = (uint) floor(n0 / 2.0);
    uint upper = (uint) floor(n1 / 2.0);
    if(distance >= lower * (time - lower)) { lower++; }
    if(distance >= upper * (time - upper)) { upper--; }
    //printf("Lower: %u, Upper: %u\n", lower, upper);
    return std::pair<uint, uint>(lower, upper);
}

uint getMargin(uint time, uint distance) {
    std::pair<uint, uint> bounds = getBounds(time, distance);
    if(bounds.first > bounds.second) { return 0; }
    return bounds.second - bounds.first + 1;

}

int main() {
    FileReader f("input.txt");
    std::vector<uint> times({});
    std::vector<uint> distances({});
    std::string line;
    line = f.nextLine(); // read times
    times = readUints(line);
    line = f.nextLine(); // read distances
    distances = readUints(line);
    uint total = 1;
    for(uint i = 0; i < times.size(); i++) {
        printf("Race %u (time %u, record %u):\n", i, times.at(i), distances.at(i));
        uint margin = getMargin(times.at(i), distances.at(i));
        printf("  %u ways to win this race.\n", margin);
        total *= margin;
    }
    printf("Total: %u.\n", total);
}
