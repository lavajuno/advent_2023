/*
 * December 8, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <numeric>
#include <vector>
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

std::vector<std::string> findStartNodes(std::map<std::string, Node>& nodes) {
    std::vector<std::string> start_nodes({});
    for(auto i = nodes.begin(); i != nodes.end(); i++) {
        if(i->first.at(2) == 'A') { start_nodes.push_back(i->first); }
    }
    return start_nodes;
}

inline bool isAtDest(std::string& key) {
    return key.at(2) == 'Z';
}

void printKeys(std::vector<std::string>& keys) {
    std::cout << "Keys:\n";
    for(uint i = 0; i < keys.size(); i++) {
        std::cout << "    " << keys.at(i) << "\n";
    }
}

u_long findSteps(std::map<std::string, Node>& nodes, std::string& instructions, 
            std::string& start_key) {
    u_long steps = 0;
    std::string curr_key = start_key;
    
    while(!isAtDest(curr_key)) {
        for(uint i = 0; i < instructions.size(); i++) {
            Node curr_node = nodes.at(curr_key);
            if(instructions.at(i) == 'L') {
                //printf("Moving left...\n");
                curr_key = curr_node.left;
                
            } else {
                //printf("Moving right...\n");
                curr_key = curr_node.right;
            }
            steps++;
            
        }
        if(isAtDest(curr_key)) { break; }
        
    }
    return steps;
}

u_long lcmv(std::vector<u_long> v, uint start, uint end) {
    if(start >= end) { return 1; }
    return std::lcm(v.at(start), lcmv(v, start + 1, end));
}

u_long lcmv(std::vector<u_long> v) {
    return lcmv(v, 0, v.size());
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

    std::vector<std::string> start_keys = findStartNodes(nodes);
    printKeys(start_keys);
    std::vector<u_long> k_steps({});
    for(uint i = 0; i < start_keys.size(); i++) {
        u_long s = findSteps(nodes, instructions, start_keys.at(i));
        printf("Start key: %s, Steps: %lu\n", start_keys.at(i).c_str(), s);
        k_steps.push_back(s);
    }

    u_long l = lcmv(k_steps);
    std::printf("Result: %lu\n", l);

    return 0;
}
