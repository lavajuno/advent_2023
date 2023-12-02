/*
 * December 1, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <filereader.hpp>

/* Returns the game's ID if the game is possible. Returns 0 if it is not. */
uint addIfPossible(std::string& line, uint limit_r, uint limit_g, uint limit_b) {
    std::stringstream lwords(line);
    std::string word;
    uint game_id = 0;
    uint max_r = 0;
    uint max_g = 0;
    uint max_b = 0;

    lwords >> word; // "Game"
    lwords >> word; // Game ID
    game_id = std::stoi(word.substr(0, word.size() - 1));
    while(!lwords.eof()) {
        uint count;
        lwords >> word; // Count
        count = std::stoi(word);
        lwords >> word; // Color
        if(word.at(word.size() - 1) == ',' || word.at(word.size() - 1) == ';') {
            word = word.substr(0, word.size() - 1); 
        }
        if(word == "red" && count > max_r) {
            max_r = count;
        } else if(word == "green" && count > max_g) {
            max_g = count;
        } else if(word == "blue" && count > max_b) {
            max_b = count;
        }
    }

    std::cout << "Game " << game_id << " - Max red: " << max_r;
    std::cout << ", Max green: " << max_g << ", Max blue: " << max_b << "\n";

    if(max_r <= limit_r && max_g <= limit_g && max_b <= limit_b) {
        return game_id;
    }
    return 0;
}

int main() {
    FileReader f("input.txt");
    uint sum = 0;
    while(!f.eof()) {
        std::string line = f.nextLine();
        sum += addIfPossible(line, 12, 13, 14);
    }
    std::cout << sum << "\n";
}
