/*
 * December 15, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <vector>
#include <filereader.hpp>

uint hash(std::string& line) {
    uint res = 0;
    for(uint i = 0; i < line.size(); i++) {
        uint c = line.at(i);
        res += c;
        res *= 17;
        res %= 256;
    }
    return res;
}

std::vector<std::string> split(std::string line, char c) {
    std::vector<std::string> res({});
    std::string buf("");
    for(uint i = 0; i < line.size(); i++) {
        if(line.at(i) == c) {
            res.push_back(buf);
            buf.clear();
        } else {
            buf += line.at(i);
        }
    }
    if(buf.size() > 0) { res.push_back(buf); }
    return res;
}

int main() {
    FileReader f("input.txt");
    std::string line = f.nextLine();
    std::vector<std::string> words = split(line, ',');

    uint sum = 0;
    for(uint i = 0; i < words.size(); i++) {
        //printf("Hash result: %u\n", hash(words.at(i)));
        sum += hash(words.at(i));
    }
    printf("Result: %u\n", sum);

    return 0;
}
