/*
 * December 10, 2023 - Puzzle 1
 * Juno Meifert
 */

#include <iostream>
#include <string>
#include <vector>
#include <filereader.hpp>

typedef std::pair<uint, uint> Pos;

/**
 * Stores a single pipe segment and provides functionality 
 * for checking connections. 
 */
class PipeSegment {
public:
    /**
     * Constructs a PipeSegment.
     */
    PipeSegment(char c, uint row, uint col) {
        this->rep = c;
        this->visited = false;
        this->row = row;
        this->col = col;
        switch(c) {
            case '|': // NS
                this->setConnects(true, true, false, false);
                break;
            case '-': // EW
                this->setConnects(false, false, true, true);
                break;
            case 'L': // NE
                this->setConnects(true, false, true, false);
                break;
            case 'J': // NW
                this->setConnects(true, false, false, true);
                break;
            case '7': // SW
                this->setConnects(false, true, false, true);
                break;
            case 'F': // SE
                this->setConnects(false, true, true, false);
                break;
            case 'S': // Start
                this->setConnects(true, true, true, true);
                break;
            default: // Not a pipe
                this->setConnects(false, false, false, false);
        }
    }

    /**
     * Prints this PipeSegment 
     */
    void print() {
        printf("%c", rep);
    }

    /**
     * @returns True if this PipeSegment connects North 
     */
    bool connectsN() { return connects_N; }

    /**
     * @returns True if this PipeSegment connects South
     */
    bool connectsS() { return connects_S; }

    /**
     * @returns True if this PipeSegment connects East
     */
    bool connectsE() { return connects_E; }

    /**
     * @returns True if this PipeSegment connects West
     */
    bool connectsW() { return connects_W; }

    /**
     * @returns True if this PipeSegment has been visited
     */
    bool isVisited() { return visited; }

    /**
     * Resets this PipeSegment's visited flag
     */
    void resetVisited() { visited = false; }

    /**
     * @returns True if this PipeSegment is the start
     */
    bool isStart() { return rep == 'S'; }

    /**
     * @returns This PipeSegment's row 
     */
    uint getRow() { return row; }

    /**
     * @returns This PipeSegment's column
     */
    uint getCol() { return col; }

    /**
     * @returns True if this PipeSegment connects to another PipeSegment
     */
    bool connectsTo(PipeSegment other) {
        //std::cout << "This: ";
        //this->print();
        //std::cout << " Other: ";
        //other.print();
        //std::cout << "\n";
        if(this->getRow() == other.getRow()) { // E/W
            if(this->getCol() == other.getCol() - 1) { // E
                return connectsToE(other);
            }
            if(this->getCol() == other.getCol() + 1) { // W
                return connectsToW(other);
            }
            std::cout << "Should not be reached! 1";
        }
        if(this->getCol() == other.getCol()) { // N/S
            if(this->getRow() == other.getRow() + 1) { // N
                return connectsToN(other);
            }
            if(this->getRow() == other.getRow() - 1) { // S
                return connectsToS(other);
            }
            std::cout << "Should not be reached! 2";
        }
        std::cout << "Should not be reached! 3";
        return false;
    }

    /**
     * @returns This PipeSegment's possible connections 
     */
    std::vector<Pos> getTries() {
        this->visited = true;
        std::vector<Pos> tries({});
        if(this->connects_N) {
            Pos t;
            t.first = this->row - 1;
            t.second = this->col;
            tries.push_back(t);
        }
        if(this->connects_S) {
            Pos t;
            t.first = this->row + 1;
            t.second = this->col;
            tries.push_back(t);
        }
        if(this->connects_E) {
            Pos t;
            t.first = this->row;
            t.second = this->col + 1;
            tries.push_back(t);
        }
        if(this->connects_W) {
            Pos t;
            t.first = this->row;
            t.second = this->col - 1;
            tries.push_back(t);
        }
        return tries;
    }

private: // data
    bool connects_N;
    bool connects_S;
    bool connects_E;
    bool connects_W;
    bool visited;
    char rep;
    uint row;
    uint col;

private: // methods
    /**
     * Sets which directions this PipeSegment can make connections in
     */
    void setConnects(bool n, bool s, bool e, bool w) {
        this->connects_N = n;
        this->connects_S = s;
        this->connects_E = e;
        this->connects_W = w;
    }

    /**
     * @returns True if this PipeSegment connects North to the other
     */
    bool connectsToN(PipeSegment& other) {
        return this->connectsN() && other.connectsS();
    }

    /**
     * @returns True if this PipeSegment connects South to the other
     */
    bool connectsToS(PipeSegment& other) {
        return this->connectsS() && other.connectsN();
    }

    /**
     * @returns True if this PipeSegment connects East to the other
     */
    bool connectsToE(PipeSegment& other) {
        return this->connectsE() && other.connectsW();
    }

    /**
     * @returns True if this PipeSegment connects West to the other
     */
    bool connectsToW(PipeSegment& other) {
        return this->connectsW() && other.connectsE();
    }
};

/**
 * @returns True if the given position is in bounds
 */
bool checkBounds(Pos p, uint n_rows, uint n_cols) {
    if(p.first < 0 || p.first >= n_rows) { return false; }
    if(p.second < 0 || p.second >= n_cols) { return false; }
    return true;
}

/**
 * Gets the next PipeSegment in the loop.
 * @param pipes 2D vector of Pipes
 * @param pos Position of the current PipeSegment
 * @param n_rows Number of rows
 * @param n_cols Number of columns
 * @param alt Whether to use the alternate path for the start pipe
 */
Pos getNext(
        std::vector<std::vector<PipeSegment>>& pipes,
        Pos pos, uint n_rows, uint n_cols, bool alt = false)
{
    std::vector<Pos> tries = pipes.at(pos.first).at(pos.second).getTries();
    std::vector<Pos> connections({});
    for(uint i = 0; i < tries.size(); i++) {
        Pos pos_try = tries.at(i);
        if(checkBounds(pos_try, n_rows, n_cols)) {
            PipeSegment pipe_try = pipes.at(pos_try.first).at(pos_try.second);
            if(pipes.at(pos.first).at(pos.second).connectsTo(pipe_try) && !pipe_try.isVisited()) {
                connections.push_back(Pos(pipe_try.getRow(), pipe_try.getCol()));
            }
        }
    }
    if(connections.size() > 1 && alt) { return connections.at(1); }
    return connections.at(0);
}

int main() {
    FileReader f("input.txt");
    std::string line;
    std::vector<std::vector<PipeSegment>> pipes({});
    Pos start_pos;
    uint row = 0;

    while(!f.eof()) {
        line = f.nextLine();
        std::vector<PipeSegment> line_pipes({});
        for(uint col = 0; col < line.size(); col++) {
            if(line.at(col) == 'S') {
                start_pos.first = row;
                start_pos.second = col;
            }
            PipeSegment p(line.at(col), row, col);
            line_pipes.push_back(p);
        }
        pipes.push_back(line_pipes);
        row++;
    }

    uint n_rows = pipes.size();
    uint n_cols = pipes.at(0).size();

    /*
    for(uint i = 0; i < pipes.size(); i++) {
        for(uint j = 0; j < pipes.at(i).size(); j++) {
            pipes.at(i).at(j).print();
        }
        printf("\n");
    }
    */
    
    uint distance = 0;
    Pos c_pos = getNext(pipes, start_pos, n_rows, n_cols, true); // move off start
    distance++;
    c_pos = getNext(pipes, c_pos, n_rows, n_cols, false); // move one more
    distance++;
    pipes.at(start_pos.first).at(start_pos.second).resetVisited(); // reset visited on start
    while(!pipes.at(c_pos.first).at(c_pos.second).isStart()) {
        c_pos = getNext(pipes, c_pos, n_rows, n_cols, false);
        distance++;
    }

    printf("Total loop distance: %u\n", distance);
    printf("Furthest point in loop: %u\n", distance / 2);

    return 0;
}
