/*
 * December 8, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <filereader.hpp>

struct Node {
    std::string left;
    std::string right;
};

std::pair<std::string, Node> readNode(std::string& line) {
    std::stringstream words(line);
    std::string word;
    std::string key;
    Node node;
    words >> key;
    words >> word; // '='
    words >> word; // left element
    node.left = word.substr(1, word.length() - 2);
    words >> word; // right element
    node.right = word.substr(0, word.length() - 1);
    return std::pair<std::string, Node>(key, node);
}

int main() {
    FileReader f("input.txt");
    std::string line;
    std::string instructions;
    std::map<std::string, Node> nodes;

    instructions = f.nextLine();
    while(!f.eof()) {
        line = f.nextLine();
        if(line.length() > 1) { nodes.emplace(readNode(line)); }
    }

    for(auto i = nodes.begin(); i != nodes.end(); i++) {
        printf(
            "Node %s: (%s, %s)\n", 
            i->first.c_str(), i->second.left.c_str(), i->second.right.c_str()
        );
    }

    uint steps = 0;
    std::string curr_key = "AAA";
    Node curr_node = nodes.at("AAA");

    while(curr_key != "ZZZ") {
        for(uint i = 0; i < instructions.size(); i++) {
            if(instructions.at(i) == 'L') {
                //printf("Moving left...\n");
                curr_key = curr_node.left;
                
            } else {
                //printf("Moving right...\n");
                curr_key = curr_node.right;
            }
            curr_node = nodes.at(curr_key);
            steps++;
        }
        if(curr_key == "ZZZ") {
            printf("Done!\n");
            break;
        }
    }
    
    printf("Steps: %u.\n", steps);

    return 0;
}
