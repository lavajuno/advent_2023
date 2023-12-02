/*
 * December 1, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <filereader.hpp>

/* Returns the minimum cubes required for a game multipled together */
uint powerCubes(std::string& line) {
    std::stringstream lstream(line);
    std::string word;
    uint game_id = 0;
    uint max_r = 0;
    uint max_g = 0;
    uint max_b = 0;

    lstream >> word; // "Game"
    lstream >> word; // Game ID
    game_id = std::stoi(word.substr(0, word.size() - 1));
    while(!lstream.eof()) {
        uint count = 0;
        lstream >> word; // Count
        count = std::stoi(word);
        lstream >> word; // Color
        // trim ',' / ';'
        char tail = word.at(word.size() - 1);
        if(tail == ',' || tail == ';') {
            word = word.substr(0, word.size() - 1); 
        }

        if(word == "red") {
            max_r = count > max_r ? count : max_r;
        } else if(word == "green") {
            max_g = count > max_g ? count : max_g;
        } else if(word == "blue") {
            max_b = count > max_b ? count : max_b;
        }
    }

    std::cout << "Game " << game_id << " - Max red: " << max_r;
    std::cout << ", Max green: " << max_g << ", Max blue: " << max_b;
    std::cout << ", Power: " << max_r * max_g * max_b << "\n";

    return max_r * max_g * max_b;
}

int main() {
    FileReader f("input.txt");
    uint sum = 0;
    while(!f.eof()) {
        std::string line = f.nextLine();
        sum += powerCubes(line);
    }
    std::cout << sum << "\n";
}
