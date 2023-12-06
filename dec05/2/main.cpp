/*
 * December 5, 2023 - Puzzle 2
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <filereader.hpp>

/* One or more MapRanges are stored in each Map */
struct MapRange {
    u_long source_start;
    u_long dest_start;
    u_long length;
};

struct Range {
    u_long start;
    u_long length;
};

/* AlmanacMap stores a single map and provides functions for mapping values */
class AlmanacMap {
public:
    /* Constructs a Map from the puzzle input */
    AlmanacMap(std::vector<std::string>& lines, uint begin_index, uint& end_index) :
            name(""),
            ranges({})
    {
        std::stringstream name_words(lines.at(begin_index));
        name_words >> name;
        int i = begin_index + 1;
        for(; lines.at(i).size() > 1; i++) {
            std::stringstream words(lines.at(i));
            std::string source_str("");
            std::string dest_str("");
            std::string length_str("");
            words >> dest_str;
            words >> source_str;
            words >> length_str;
            MapRange r;
            r.source_start = stol(source_str);
            r.dest_start = stol(dest_str);
            r.length = stol(length_str);
            ranges.push_back(r);
        }
        end_index = i;
    }

    /* Maps a source to a destination using this map */
    u_long mapDest(u_long source) {
        for(uint i = 0; i < ranges.size(); i++) {
            if(inRange(ranges.at(i), source)) {
                return mapRange(ranges.at(i), source);
            }
        }
        return source;
    }

    /* Prints this AlmanacMap for debugging */
    void print() {
        std::cout << "Map \"" << name << "\":\n";
        std::cout << "  Ranges:\n";
        for(int i = 0; i < ranges.size(); i++) {
            MapRange r = ranges.at(i);
            std::cout << r.source_start << " -> " << r.dest_start << " (" << r.length << ")\n";
        }
    }

    /* Returns this AlmanacMap's name */
    std::string getName() { return name; }

private:
    std::string name;
    std::vector<MapRange> ranges;

    /* True if given number is in the given range */
    bool inRange(MapRange r, u_long n) {
        return n >= r.source_start && n < r.source_start + r.length;
    }

    /* Maps a number with a range (assumes the number is in the range!) */
    u_long mapRange(MapRange r, u_long n) {
        return r.dest_start + (n - r.source_start);
    }

};

/* Advances the given iterator past whitespace */
void munchWhitespace(std::vector<std::string>& lines, uint& i) {
    for(; i < lines.size() && lines.at(i).size() <= 1; i++);
}

/* Gets the seed numbers at the top of the puzzle input */
std::vector<u_long> getSeeds(std::string line) {
    std::vector<u_long> seeds({});
    std::stringstream words(line);
    std::string word("");
    words >> word; // "seeds:"
    while(!words.eof()) {
        words >> word;
        seeds.push_back(stol(word));
    }
    return seeds;
}

/* Finds a path through all the maps for a seed number */
u_long journey(std::vector<AlmanacMap>& maps, u_long source) {
    u_long m_sd = source;
    for(uint i = 0; i < maps.size(); i++) {
        m_sd = maps.at(i).mapDest(m_sd);
    }
    return m_sd;
}

int main() {
    FileReader f("input.txt");
    std::vector<std::string> lines({});
    while(!f.eof()) {
        std::string line = f.nextLine();
        lines.push_back(line);
    }

    std::vector<u_long> seeds = getSeeds(lines.at(0));
    std::vector<AlmanacMap> maps({});

    uint i = 1;
    munchWhitespace(lines, i);
    while(i < lines.size() - 1) {
        uint begin = i;
        maps.push_back(AlmanacMap(lines, begin, i));
        munchWhitespace(lines, i);
    }
    // Definitely not the right way to do it but it doesn't take too long
    u_long min = (u_long) -1;
    for(uint j = 0; j < seeds.size(); j += 2) {
        u_long start = seeds.at(j);
        u_long end = start + seeds.at(j + 1);
        std::cout << "Start: " << start << " End: " << end << "\n";
        for(u_long k = start; k < end; k++) {
            u_long loc = journey(maps, k);
            if(loc < min) { min = loc; }
        }
    }
    std::cout << min << "\n";
}
