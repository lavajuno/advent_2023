/*
 * December 6, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <vector>
#include <filereader.hpp>

u_long readUlong(std::string& line) {
    std::stringstream words(line);
    std::string word;
    std::string value;

    words >> word; // "Time:" or "Distance:"
    while(!words.eof()) {
        words >> word;
        value += word;
    }
    return stol(value);
}

std::pair<u_long, u_long> getBounds(u_long time, u_long distance) {
    double d_time = (double) time;
    double d_distance = (double) distance;
    double n0 = 1 * d_time - sqrt(pow(d_time, 2) - 4 * d_distance);
    double n1 = 1 * d_time + sqrt(pow(d_time, 2) - 4 * d_distance);
    u_long lower = (u_long) floor(n0 / 2.0);
    u_long upper = (u_long) floor(n1 / 2.0);
    if(distance >= lower * (time - lower)) { lower++; }
    if(distance >= upper * (time - upper)) { upper--; }
    //printf("Lower: %lu, Upper: %lu\n", lower, upper);
    return std::pair<u_long, u_long>(lower, upper);
}

uint getMargin(u_long time, u_long distance) {
    std::pair<u_long, u_long> bounds = getBounds(time, distance);
    if(bounds.first > bounds.second) { return 0; }
    return bounds.second - bounds.first + 1;

}

int main() {
    FileReader f("input.txt");
    std::string line;
    line = f.nextLine(); // read times
    u_long time = readUlong(line);
    line = f.nextLine(); // read distances
    u_long distance = readUlong(line);

    printf("Race (time %lu, record %lu):\n", time, distance);
    u_long margin = getMargin(time, distance);
    printf("  %lu ways to win this race.\n", margin);
}