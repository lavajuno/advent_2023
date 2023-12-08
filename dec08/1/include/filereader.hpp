#pragma once

#include <iostream>
#include <fstream>

class FileReader {
public:
    FileReader(std::string file_path) {
        this->f_input.open(file_path);
        if(!this->f_input.is_open()) {
            std::cerr << "Failed to open \"" << file_path << "\".\n";
        }
    }

    ~FileReader() {
        this->f_input.close();
    }

    std::string nextLine() {
        if(this->f_input.eof()) { return NULL; }
        std::string line;
        std::getline(f_input, line);
        return line;
    }

    bool eof() { return this->f_input.eof(); }

private:
    std::ifstream f_input;
};