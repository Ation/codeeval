#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

class Path {
public:
    explicit Path(unsigned int x_size, unsigned int y_size, unsigned int x_position, unsigned int y_position) : m_xPosition(x_position), m_yPosition(y_position) {
        m_path.resize(y_size);
        for(auto&& v : m_path) {
            v.resize(x_size, false);
        }
        m_path[m_yPosition][m_xPosition] = true;
        m_step = 1;
    }

    Path(const Path& src) : m_xPosition(src.m_xPosition), m_yPosition(src.m_yPosition), m_path(src.m_path), m_step(src.m_step) {
    }

    ~Path() = default;

    void moveUp() {
        m_yPosition--;
        m_path[m_yPosition][m_xPosition] = true;
        m_step++;
    }
    void moveDown() {
        m_yPosition++;
        m_path[m_yPosition][m_xPosition] = true;
        m_step++;
    }
    void moveLeft() {
        m_xPosition--;
        m_path[m_yPosition][m_xPosition] = true;
        m_step++;
    }
    void moveRight() {
        m_xPosition++;
        m_path[m_yPosition][m_xPosition] = true;
        m_step++;
    }

    unsigned int x_position() const {
        return m_xPosition;
    }

    unsigned int y_position() const {
        return m_yPosition;
    }

    bool reachEnd( const string &word) {
        return m_step == word.length();
    }

    bool canMoveUp(const vector<string> &grid_data, const string &word) const {
        return (m_step < word.length() ) && (m_yPosition != 0) && (! m_path[m_yPosition - 1][m_xPosition] ) && ( grid_data[m_yPosition - 1][m_xPosition] == word[m_step] );
    }
    bool canMoveDown(const vector<string> &grid_data, const string &word) const {
        return (m_step < word.length() ) && (m_yPosition != m_path.size() - 1) && (! m_path[m_yPosition + 1][m_xPosition] ) && ( grid_data[m_yPosition + 1][m_xPosition] == word[m_step] );
    }
    bool canMoveLeft(const vector<string> &grid_data, const string &word) const {
        return (m_step < word.length() ) && (m_xPosition != 0) && (! m_path[m_yPosition][m_xPosition - 1] ) && ( grid_data[m_yPosition][m_xPosition - 1] == word[m_step] );
    }
    bool canMoveRight(const vector<string> &grid_data, const string &word) const {
        return (m_step < word.length() ) && (m_xPosition != m_path[0].size() - 1)  && (! m_path[m_yPosition][m_xPosition + 1] ) && ( grid_data[m_yPosition][m_xPosition + 1] == word[m_step] );
    }

private:
    unsigned int m_xPosition;
    unsigned int m_yPosition;
    unsigned int m_step;

    vector < vector<bool> > m_path;
};

class Grid {
public:
    Grid(const Grid& ) = delete;

    Grid ( const vector<string> &grid_data) : m_gridData(grid_data) {
        unsigned int x_size = grid_data[0].length();
        unsigned int y_size = grid_data.size();

        // create starting path list
        for (unsigned int y=0; y < y_size; y++) {
            for (unsigned int x=0; x < x_size; x++ ) {
                m_startingPositions[ grid_data[y][x] ].emplace_back( x_size, y_size, x, y );
            }
        }
    }

    bool findWord( const string &word) {
        auto&& it = m_startingPositions.find(word[0]);
        if (it == m_startingPositions.end()) {
            return false;
        }

        list<Path> options( it->second.begin(), it->second.end() );


        while ( !options.empty() ) {
            if (options.begin()->canMoveUp(m_gridData, word)) {
                Path nextStep( *options.begin());
                nextStep.moveUp();
                if (nextStep.reachEnd(word)) {
                    return true;
                }
                options.push_back(nextStep);
            }
            if (options.begin()->canMoveDown(m_gridData, word)) {
                Path nextStep( *options.begin());
                nextStep.moveDown();
                if (nextStep.reachEnd(word)) {
                    return true;
                }
                options.push_back(nextStep);
            }
            if (options.begin()->canMoveLeft(m_gridData, word)) {
                Path nextStep( *options.begin());
                nextStep.moveLeft();
                if (nextStep.reachEnd(word)) {
                    return true;
                }
                options.push_back(nextStep);
            }
            if (options.begin()->canMoveRight(m_gridData, word)) {
                Path nextStep( *options.begin());
                nextStep.moveRight();
                if (nextStep.reachEnd(word)) {
                    return true;
                }
                options.push_back(nextStep);
            }

            options.pop_front();
        }

        return !options.empty();
    }

private:
    map< char, vector < Path > > m_startingPositions;
    vector< string > m_gridData;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    vector < string > gridData = {"ABCE", "SFCS", "ADEE"};
    Grid grid(gridData);

    while ( getline(inFile, inputLine)) {
        cout << (grid.findWord(inputLine) ? "True" : "False" ) << endl;
    }

    return 0;
}
