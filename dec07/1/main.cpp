/*
 * December 7, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <filereader.hpp>

class Hand {
public:
    Hand(std::string line) : 
            h_type(0), 
            h_bid(0),
            h_cards("") 
    {
        std::stringstream words(line);
        std::string word;
        words >> h_cards;
        words >> word;
        h_bid = std::stoi(word);
        h_type = matchType(h_cards);
    }

    uint getType() { return h_type; }

    uint getBid() { return h_bid; }

    std::string getCards() { return h_cards; }

    void print() { 
        printf("Hand: \"%s\" (%u) - %u\n", h_cards.c_str(), h_type, h_bid);
    }

    static bool compare(Hand& a, Hand& b) {
        if(a.getType() < b.getType()) { return true; }
        if(a.getType() > b.getType()) { return false; }
        return breakTie(a.getCards(), b.getCards());
    }

private:
    uint h_type;
    uint h_bid;
    std::string h_cards;

private:
    uint matchType(std::string& cards) {
        std::vector<uint> counts = countUniques(cards);
        uint type = 0;
        if(isFiveOfKind(counts))       { type = 6; }
        else if(isFourOfKind(counts))  { type = 5; }
        else if(isFullHouse(counts))   { type = 4; }
        else if(isThreeOfKind(counts)) { type = 3; }
        else if(isTwoPair(counts))     { type = 2; }
        else if(isOnePair(counts))     { type = 1; }
        printf("Hand: \"%s\" - Matched type: %u\n", cards.c_str(), type);
        return type;
    }

    inline bool isFiveOfKind(std::vector<uint> counts) {
        return counts.size() == 1;
    }

    inline bool isFourOfKind(std::vector<uint> counts) {
        return counts.size() == 2 && counts.at(0) == 1;
    }

    inline bool isFullHouse(std::vector<uint> counts) {
        return counts.size() == 2 && counts.at(0) == 2;
    }

    inline bool isThreeOfKind(std::vector<uint> counts) {
        return counts.size() == 3 && counts.at(2) == 3;
    }

    inline bool isTwoPair(std::vector<uint> counts) {
        return counts.size() == 3 && counts.at(0) == 1 && counts.at(1) == 2;
    }

    inline bool isOnePair(std::vector<uint> counts) {
        return counts.size() == 4;
    }

    std::string findUniques(std::string& cards) {
        std::string uniques("");
        for(uint i = 0; i < cards.length(); i++) {
            bool flag_unique = true;
            for(uint j = 0; j < uniques.length(); j++) {
                if(cards.at(i) == uniques.at(j)) { flag_unique = false; }
            }
            if(flag_unique) { uniques.push_back(cards.at(i)); }
        }
        return uniques;
    }

    uint countInstances(std::string& cards, char card) {
        uint count = 0;
        for(uint i = 0; i < cards.length(); i++) {
            if(cards.at(i) == card) { count++; }
        }
        return count;
    }
    
    std::vector<uint> countUniques(std::string& cards) {
        std::string uniques = findUniques(cards);
        std::vector<uint> counts({});
        for(uint i = 0; i < uniques.size(); i++) {
            counts.push_back(countInstances(cards, uniques.at(i)));
        }
        std::sort(counts.begin(), counts.end());
        return counts;
    }

    static uint scoreCard(char card) {
        switch(card) {
            case 'A': return 14;
            case 'K': return 13;
            case 'Q': return 12;
            case 'J': return 11;
            case 'T': return 10;
            default: return card - '0';
        }
    }

    static bool breakTie(std::string a_cards, std::string b_cards) {
        for(uint i = 0; i < a_cards.length(); i++) {
            uint a_score = scoreCard(a_cards.at(i));
            uint b_score = scoreCard(b_cards.at(i));
            if(a_score < b_score) { return true; }
            if(a_score > b_score) { return false; }
        }
        std::cout << "Uh-oh!\n";
        return false;
    }

};

int main() {
    FileReader f("input.txt");
    std::string line;
    std::vector<Hand> hands({});
    while(!f.eof()) {
        line = f.nextLine();
        Hand h(line);
        hands.push_back(h);
    }
    std::sort(hands.begin(), hands.end(), Hand::compare);

    u_long winnings = 0;
    for(uint i = 0; i < hands.size(); i++) {
        hands.at(i).print();
        printf("  Winnings: %u\n", hands.at(i).getBid() * (i + 1));
        winnings += (u_long) hands.at(i).getBid() * (i + 1);
    }
    printf("Result: %lu\n", winnings);
    return 0;
}