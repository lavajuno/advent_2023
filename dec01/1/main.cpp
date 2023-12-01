
#include <iostream>
#include <string>
#include <filereader.hpp>

uint flDigits(std::string& line) {
    uint result = 0;
    /* find first digit */
    for(int i = 0; i < line.length(); i++) {
        char c = line.at(i);
        if(c >= '0' && c <= '9') {
            result += (c - '0') * 10;
            break;
        }
    }
    /* find last digit */
    for(int i = line.length() - 1; i >= 0; i--) {
        char c = line.at(i);
        if(c >= '0' && c <= '9') {
            result += c - '0';
            break;
        }
    }
    return result;
}

int main() {
    FileReader f("input.txt");
    uint sum = 0;
    while(!f.eof()) {
        std::string line = f.nextLine();
        sum += flDigits(line);
    }
    std::cout << sum << "\n";
}

