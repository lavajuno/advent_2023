/*
 * December 4, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <math.h>
#include <filereader.hpp>

struct Card {
    uint id;
    uint matches;
    uint count;
};

void printCard(Card card) {
    std::cout << "{ id: " << card.id << ", matches: " << card.matches << ", count: " << card.count << " }\n";
}

Card cardFromLine(std::string& line) {
    std::vector<uint> winning_numbers;
    uint matches = 0;
    std::stringstream words(line);
    std::string word;
    uint id;

    words >> word; // "Card"
    words >> word; // Card ID
    id = std::stoi(word.substr(0, word.length() - 1));

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
    Card card;
    card.matches = matches;
    card.id = id;
    card.count = 1;
    return card;
}

std::vector<Card> assemble(std::vector<std::string>& lines) {
    std::vector<Card> cards({});
    for(int i = 0; i < lines.size(); i++) {
        std::cout << "Line: \"" << lines.at(i) << "\"\n";
        printCard(cardFromLine(lines.at(i)));
        cards.push_back(cardFromLine(lines.at(i)));
    }
    return cards;
}

void score(std::vector<Card>& cards) {
    uint size = cards.size();
    uint i = 0;
    for(uint i = 0; i < cards.size(); i++) {
        Card c = cards.at(i);
        std::cout << "Scoring card " << c.id << " (" << c.count << " copies, " << c.matches << " matches).\n";
        for(uint j = c.id; j < c.id + c.matches; j++) {
            std::cout << "  " << c.count << " copies of card " << cards.at(j).id << " won.\n";
            cards.at(j).count += c.count;
        }
    }
}

uint sum(std::vector<Card>& cards) {
    uint sum = 0;
    for(uint i = 0; i < cards.size(); i++) { sum += cards.at(i).count; }
    return sum;
}

int main() {
    FileReader f("input.txt");
    std::vector<std::string> lines({});
    while(!f.eof()) {
        std::string line = f.nextLine();
        lines.push_back(line);
    }
    std::vector<Card> cards = assemble(lines);
    score(cards);
    std::cout << "Total cards: " << sum(cards) << ".\n";
}
