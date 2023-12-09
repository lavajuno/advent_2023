/*
 * December 9, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <filereader.hpp>

std::vector<long> getDiffs(std::vector<long>& scan) {
    std::vector<long> diffs({});
    for(uint i = 1; i < scan.size(); i++) {
        diffs.push_back(scan.at(i) - scan.at(i - 1));
    }
    return diffs;
}

bool isZeroes(std::vector<long>& scan) {
    for(uint i = 0; i < scan.size(); i++) {
        if(scan.at(i) != 0) { return false; }
    }
    return true;
}

long extrapolate(std::vector<long>& scan) {
    if(isZeroes(scan)) { return 0; }
    std::vector<long> diffs = getDiffs(scan);
    return scan.at(scan.size() - 1) + extrapolate(diffs);
}

std::vector<long> parseLine(std::string& line) {
    std::vector<long> values({});
    std::stringstream words(line);
    std::string word;
    while(!words.eof()) {
        words >> word;
        values.push_back(std::stol(word));
    }
    return values;
}

int main() {
    FileReader f("input.txt");
    std::string line;
    long sum;
    while(!f.eof()) {
        line = f.nextLine();
        std::vector<long> v = parseLine(line);
        sum += extrapolate(v);
    }
    printf("Sum: %li\n", sum);
    return 0;
}
