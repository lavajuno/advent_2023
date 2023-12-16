/*
 * December 16, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <filereader.hpp>

typedef std::pair<int, int> Pos;

class Tile {
public:
    Tile(char symbol, bool energized) : symbol(symbol), energized(energized) {}

    char getSymbol() { return symbol; }

    bool isEnergized() { return energized; }

    void energize() { energized = true; }

    void print() {
        std::cout << symbol;
        /*
        if(energized) {
            std::cout << "#";
        } else {
            std::cout << symbol;
        }
        */
    }

private:
    char symbol;
    bool energized;

};

struct Visit {
    Pos pos;
    int dir_row;
    int dir_col;
};

class Beam {
public:
    Beam(Pos pos, int dir_row, int dir_col) :
            pos(pos),
            dir_row(dir_row),
            dir_col(dir_col)
    {}

    int getDirRow() { return dir_row; }

    int getDirCol() { return dir_col; }

    Pos getPos() { return pos; }

    Pos peek() { return Pos(pos.first + dir_row, pos.second + dir_col); }

    void step() { pos = Pos(pos.first + dir_row, pos.second + dir_col); }

    void visit() {
        Visit v;
        v.pos = pos;
        v.dir_row = dir_row;
        v.dir_col = dir_col;
    }

private:
    Pos pos;
    int dir_row;
    int dir_col;
};

class Grid {
public:
    Grid(std::vector<std::string>& lines) : tiles({}), beams() {
        for(uint i = 0; i < lines.size(); i++) {
            std::vector<Tile> line_tiles({});
            for(uint j = 0; j < lines.at(0).size(); j++) {
                Tile t(lines.at(i).at(j), false);
                line_tiles.push_back(t);
            }
            tiles.push_back(line_tiles);
        }
        Beam b(Pos(0, 0), 0, 1);
        beams.push_back(b);
    }

    Tile& at(Pos p) { return tiles.at(p.first).at(p.second); }

    int nRows() { return tiles.size(); }

    int nCols() { return tiles.at(0).size(); }

    void print(Pos p) {
        for(int i = 0; i < this->nRows(); i++) {
            for(int j = 0; j < this->nCols(); j++) {
                if(Pos(i, j) == p) {
                    std::cout << "O";
                } else {
                    this->at(Pos(i, j)).print();
                }
                

            }
            std::cout << "\n";
        }
    }

    void traceBeams() {
        int i = 0;
        while(!beams.empty()) { 
            std::cout << "\n\nStepping "<< i << "\n";
            this->step();
            this->print(beams.back().getPos());
            this->printBeams();
            i++;
            int ignored;
            std::cin >> ignored;
            if(i > 600) { break; }
        }
    }

private:
    std::vector<std::vector<Tile>> tiles;
    std::deque<Beam> beams;

private:
    bool checkBounds(Pos p) {
        if(p.first < 0) { return false; }
        if(p.first >= this->nRows()) { return false; }
        if(p.second < 0) { return false; }
        if(p.second >= this->nCols()) { return false; }
        return true;
    }

    void printBeams() {
        for(int i = beams.size() - 1; i >= 0; i--) {
            Beam b = beams.at(i);
            printf(
                "Pos: (%d, %d), Dir: (%d, %d)\n",
                b.getPos().first,
                b.getPos().second,
                b.getDirRow(),
                b.getDirCol()
            );
        }
    }

    void step() {
        if(beams.empty()) { return; }
        Beam b = beams.back();
        beams.pop_back();
        this->at(b.getPos()).energize();
        if(!checkBounds(b.peek())) { return; }
        switch(this->at(b.peek()).getSymbol()) {
            case '/':
                b.visit();
                if(b.getDirRow() == 0) { // horizontal
                    Beam n(b.peek(), -b.getDirCol(), 0);
                    if(!isDuplicate(n)) { beams.push_back(n); }
                } else { // vertical
                    Beam n(b.peek(), 0, -b.getDirRow());
                    if(!isDuplicate(n)) { beams.push_back(n); }
                }
                break;
            case '\\':
                b.visit();
                if(b.getDirRow() == 0) { // horizontal
                    Beam n(b.peek(), b.getDirCol(), 0);
                    if(!isDuplicate(n)) { beams.push_back(n); }
                } else { // vertical
                    Beam n(b.peek(), 0, b.getDirRow());
                    if(!isDuplicate(n)) { beams.push_back(n); }
                }
                break;
            case '-':
                b.visit();
                if(b.getDirRow() == 0) { // horizontal
                    b.step();
                    beams.push_back(b);
                } else { // vertical
                    Beam r(b.peek(), 0, 1);
                    Beam l(b.peek(), 0, -1);
                    if(!isDuplicate(r)) { beams.push_back(r); }
                    if(!isDuplicate(l)) { beams.push_back(l); }
                }
                break;
            case '|':
                b.visit();
                if(b.getDirRow() == 0) { // horizontal
                    Beam up(b.peek(), -1, 0);
                    Beam dn(b.peek(), 1, 0);
                    if(!isDuplicate(up)) { beams.push_back(up); }
                    if(!isDuplicate(dn)) { beams.push_back(dn); }
                } else { // vertical
                    b.step();
                    if(!isDuplicate(b)) { beams.push_back(b); }
                }
                break;
            default:
                b.step();
                if(!isDuplicate(b)) { beams.push_back(b); }
        }
    }

    bool isDuplicate(Beam b) {
        for(int i = beams.size() - 1; i >= 0; i--) {
            Beam a = beams.at(i);
            if(a.getPos() == b.getPos() && a.getDirRow() == b.getDirRow() 
                    && a.getDirCol() == b.getDirCol()) {
                std::cout << "Duplicate found\n";
                return true;
            }
        }
        return false;
    }
};

int main() {
    FileReader f("input.txt");
    std::vector<std::string> lines({});
    while(!f.eof()) {
        std::string line = f.nextLine();
        lines.push_back(line);
    }
    Grid grid(lines);

    grid.traceBeams();

    return 0;
}
