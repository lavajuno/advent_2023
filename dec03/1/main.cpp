/*
 * December 3, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <filereader.hpp>

/**
 * Returns a string containing the symbols immediately surrounding a number.
 */
std::string perimeter(std::vector<std::string>& lines, 
                    uint l_index, uint n_start, uint n_length) {
    std::stringstream s;
    uint adj_start;
    uint adj_len;

    // Handle special cases for numbers at start/end of line
    if(n_start + n_length >= lines.at(l_index).length()) {
        // number is at end of string, do not go past it
        adj_start = n_start - 1;
        adj_len = n_length + 1;
    } else if(n_start == 0) {
        // number is at start of string, do not go before it
        adj_start = n_start;
        adj_len = n_length + 1;
    } else {
        // number is somewhere in the middle of the line, no special handling
        adj_start = n_start - 1;
        adj_len = n_length + 2;
    }

    if(l_index > 0) {
        // First line in input, do not go above it
        s << lines.at(l_index - 1).substr(adj_start, adj_len);
    }
    s << lines.at(l_index).substr(adj_start, adj_len);
    if(l_index < lines.size() - 1) {
        // Last line in input, do not go below it
        s << lines.at(l_index + 1).substr(adj_start, adj_len);
    }
    return s.str();
}

/**
 * Returns true if a given perimiter contains a valid part number.
 */
bool isPart(std::string perim) {
    for(int i = 0; i < perim.length(); i++) {
        char c = perim.at(i);
        if((c < '0' || c > '9') && c != '.') {
            return true;
        }
    }
    return false;
}

/**
 * Finds the length of a number given the start index 
 */
uint findNumLength(std::string line, uint start) {
    for(uint i = start; i < line.size(); i++) {
        char c = line.at(i);
        if(c < '0' || c > '9') { return i - start; }
    }
    return line.size() - start;
}

/**
 * Returns the sum of all of the part numbers in a line 
 */
uint sumPartsLine(std::vector<std::string>& lines, uint line_index) {
    std::string line = lines.at(line_index);
    uint sum = 0;
    for(uint i = 0; i < line.size(); i++) {
        char c = line.at(i);
        if(c >= '0' && c <= '9') {
            uint num_len = findNumLength(line, i);
            std::string perim = perimeter(lines, line_index, i, num_len);
            if(isPart(perim)) {
                std::cout << "  Found part " << std::stoi(line.substr(i, num_len)) << ".\n";
                sum += std::stoi(line.substr(i, num_len));
            }
            i += (num_len - 1);
        }
    }
    return sum;
}

/**
 * Returns the sum of all of the part numbers in a schematic
 */
uint sumPartsSchema(std::vector<std::string>& lines) {
    uint curr_line = 0;
    uint curr_char = 0;
    uint sum = 0;
    for(uint i = 0; i < lines.size(); i++) {
        //std::cout << "Scanning line " << i << ".\n";
        sum += sumPartsLine(lines, i);
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
    uint sum = sumPartsSchema(lines);
    std::cout << sum << "\n";
}
