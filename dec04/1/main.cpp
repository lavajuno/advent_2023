/*
 * December 4, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <math.h>
#include <filereader.hpp>

uint scoreLine(std::string& line) {
    std::vector<uint> winning_numbers;
    uint matches = 0;
    std::stringstream words(line);
    std::string word;

    words >> word; // "Card"
    words >> word; // Card ID

    // Record winning numbers
    while(!words.eof()) {
        words >> word;
        if(word == "|") { break; }
        winning_numbers.push_back(std::stoi(word));
    }

    // Check our numbers against winning numbers
    while(!words.eof()) {
        words >> word;
        uint current_number = std::stoi(word);
        for(uint i = 0; i < winning_numbers.size(); i++) {
            if(winning_numbers.at(i) == current_number) { 
                std::cout << "  Found winning number " << current_number << "\n";
                matches++;
            }
        }
    }

    if(matches > 0) { return pow(2, matches - 1); }
    return 0;
}

int main() {
    FileReader f("input.txt");
    std::vector<std::string> lines;
    uint sum = 0;
    while(!f.eof()) {
        std::string line = f.nextLine();
        std::cout << "Line: \"" << line << "\"\n";
        uint score = scoreLine(line);
        std::cout << "  Score: " << score << "\n";
        sum += score;
    }
    std::cout << sum << "\n";
}
