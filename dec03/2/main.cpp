/*
 * December 3, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <vector>
#include <filereader.hpp>

/**
 * Returns true if the given char is a digit
 */
inline bool isDigit(char n) { return n >= '0' && n <= '9'; }

/**
 * Returns the number that the given index points to
 */
uint parseNumber(std::string& line, uint n_index) {
    uint n_start = n_index;
    while(n_start > 0 && isDigit(line.at(n_start))) { n_start--; }
    if(!isDigit(line.at(n_start))) { n_start++; }
    uint n_end = n_start;
    while(n_end < line.size() && isDigit(line.at(n_end))) { n_end++; }
    return std::stoi(line.substr(n_start, n_end - n_start));
}

/**
 * Finds part numbers given indices that point to them
 */
std::vector<uint> coordsToParts(std::vector<std::string>& lines, std::vector<uint>& coords) {
    std::vector<uint> parts;
    for(int i = 0; i < coords.size(); i += 2) {
        std::string line = lines.at(coords.at(i));
        parts.push_back(parseNumber(line, coords.at(i + 1)));
    }
    return parts;
}

/**
 * Finds incides of part numbers adjacent to a star
 */
std::vector<uint> gearCoords(std::vector<std::string>& lines, 
                            uint l_index, uint s_index) {
    uint line_len = lines.at(l_index).length();
    std::vector<uint> coords;

    // handle special cases for start/end of input/line
    uint l_start = l_index > 0 ? l_index - 1 : 0;
    uint l_end = l_index >= lines.size() - 1 ? l_index : l_index + 1;
    uint c_start = s_index > 0 ? s_index - 1 : 0;
    uint c_end = s_index >= line_len - 1 ? s_index : s_index + 1;

    // step through lines - not O(n^2)
    for(int i = l_start; i <= l_end; i++) {
        std::string line = lines.at(i);
        bool flag_dupe = false;
        // step through characters
        for(int j = c_start; j <= c_end; j++) {
            char c = line.at(j);
            if(isDigit(c)) {
                // don't record the same number twice
                if(!flag_dupe) {
                    std::cout << "  Found a part at " << i << "," << j << "\n";
                    coords.push_back(i); // line index
                    coords.push_back(j); // char index
                    flag_dupe = true;
                }
            } else {
                // reset dupe flag when a non-number character is seen
                flag_dupe = false;
            }
        }
    }
    return coords;
}

/**
 * Returns the sum of all of the gear ratios in a line 
 */
uint sumGearsLine(std::vector<std::string>& lines, uint line_index) {
    std::string line = lines.at(line_index);
    uint sum = 0;
    for(uint i = 0; i < line.size(); i++) {
        char c = line.at(i);
        if(c == '*') {
            std::cout << "Found a star at " << line_index << "," << i << "\n";
            std::vector<uint> coords = gearCoords(lines, line_index, i);
            std::vector<uint> parts = coordsToParts(lines, coords);
            if(parts.size() == 2) {
                std::cout << "  Ratio: " << parts.at(0) << " * " << parts.at(1) << "\n";
                sum += parts.at(0) * parts.at(1);
            } else {
                std::cout << "  Not a gear ratio.\n";
            }
        }
    }
    return sum;
}

/**
 * Returns the sum of all of the gear ratios in a schematic
 */
uint sumGearsSchema(std::vector<std::string>& lines) {
    uint curr_line = 0;
    uint curr_char = 0;
    uint sum = 0;
    for(uint i = 0; i < lines.size(); i++) {
        sum += sumGearsLine(lines, i);
    }
    return sum;
}

int main() {
    FileReader f("input.txt");
    std::vector<std::string> lines;
    while(!f.eof()) {
        std::string line = f.nextLine();
        lines.push_back(line);
    }
    uint sum = sumGearsSchema(lines);
    std::cout << sum << "\n";
}
