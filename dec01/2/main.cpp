/*
 * December 1, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <filereader.hpp>

/* Pushes a character onto a buffer */
void push(std::string& buf, char c, bool rev) {
    buf = rev ? buf.substr(0, 4) : buf.substr(1, 4);
    if(rev) {
        buf = c + buf;
    } else {
        buf += c;
    }
}

/* Checks if a buffer matches a string, returns as soon as it can decide */
bool matchStr(std::string& buf, std::string cmp, bool rev) {
    uint dif = rev ? 0 : buf.length() - cmp.length();

    for(uint i = 0; i < cmp.length(); i++) {
        if(buf.at(i + dif) != cmp.at(i)) { return false; }
    }
    return true;
}

/* Matches a buffer to a digit. Not a fantastic way to do it but oh well */
char matchDigit(std::string& buf, bool rev) {
    if(matchStr(buf, "one", rev)) { return '1'; }
    if(matchStr(buf, "two", rev)) { return '2'; }
    if(matchStr(buf, "three", rev)) { return '3'; }
    if(matchStr(buf, "four", rev)) { return '4'; }
    if(matchStr(buf, "five", rev)) { return '5'; }
    if(matchStr(buf, "six", rev)) { return '6'; }
    if(matchStr(buf, "seven", rev)) { return '7'; }
    if(matchStr(buf, "eight", rev)) { return '8'; }
    if(matchStr(buf, "nine", rev)) { return '9'; }
    return 'x';
}

/* Finds the sum of the first and last digits in the input string */
uint flDigits(std::string& line) {
    uint result = 0;
    std::string buf = "-----";
    /* find first digit */
    for(int i = 0; i < line.length(); i++) {
        /* search for characters */
        char c = line.at(i);
        if(c >= '0' && c <= '9') {
            result += (c - '0') * 10;
            break;
        }
        /* search for words */
        push(buf, c, false);
        char m = matchDigit(buf, false);
        if(m != 'x') {
            result += (m - '0') * 10;
            break;
        }
    }

    /* find last digit */
    buf = "-----";
    for(int i = line.length() - 1; i >= 0; i--) {
        /* search for characters */
        char c = line.at(i);
        if(c >= '0' && c <= '9') {
            result += c - '0';
            break;
        }
        /* search for words */
        push(buf, c, true);
        char m = matchDigit(buf, true);
        if(m != 'x') {
            result += m - '0';
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
