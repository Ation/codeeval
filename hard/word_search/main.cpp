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

static const unsigned int max_x = 4;
static const unsigned int max_y = 3;

typedef struct __path {
    __path(unsigned int _x, unsigned int _y) : x(_x), y(_y), step(1) {
        memset(grid_path, 0, sizeof(char) * max_x * max_y);
        grid_path[y][x] = 1;
    }

    unsigned int x;
    unsigned int y;

    unsigned int step;

    char grid_path[max_y][max_x];
}path;

static const char grid_data[max_y + 1][max_x + 1] = {"ABCE", "SFCS", "ADEE"};

class Grid {
public:
    Grid() {
        for ( unsigned int y=0; y < max_y; y++) {
            for (unsigned int x=0; x < max_x; x++) {
                m_startingPositions[ grid_data[y][x] ].emplace_back(x, y);
            }
        }
    }

    bool findWord( const string &word) {
        auto &&it = m_startingPositions.find(word[0]);
        if (it == m_startingPositions.end()) {
            return false;
        }

        list<path> possible_path_list( it->second.begin(), it->second.end());

        while (!possible_path_list.empty()) {
            path& current = possible_path_list.front();

            while (current.step != word.length() ) {
                char current_symbol = word[current.step - 1];
                char next_symbol = word[current.step];

                if (current_symbol == 'S') {
                    if ((next_symbol == 'A') || (next_symbol == 'E') ) {
                        if ( current.grid_path[ 0 ][ current.x ] == 0 ) {
                            if (current.grid_path[ 2 ][ current.x ] == 0) {
								path next(current);
								next.grid_path[0][current.x] = 1;
                                possible_path_list.push_back( next );
                            }
                            current.step++;
                            current.y = 0;
                            current.grid_path[ current.y ][ current.x ] = 1;
                            continue;
                        } else {
                            if (current.grid_path[ 2 ][ current.x ] != 0) {
                                return false;
                            }
                            current.step++;
                            current.y = 2;
                            current.grid_path[ current.y ][ current.x ] = 1;
                            continue;
                        }
                    }
                }

                if (( current.y != 0 ) && ( current.grid_path[ current.y - 1 ][current.x] == 0) ) {
                    if ( grid_data[current.y - 1][current.x] == next_symbol ) {
                        current.step++;
                        current.y--;
						current.grid_path[current.y][current.x] = 1;
                        continue;
                    }
                }
                if (( current.y < max_y - 1 ) && ( current.grid_path[ current.y + 1 ][current.x] == 0) ) {
                    if ( grid_data[current.y + 1][current.x] == next_symbol ) {
                        current.step++;
                        current.y++;
						current.grid_path[current.y][current.x] = 1;
                        continue;
                    }
                }
                if (( current.x != 0 ) && ( current.grid_path[ current.y ][current.x - 1] == 0) ) {
                    if ( grid_data[current.y][current.x - 1] == next_symbol ) {
                        current.step++;
                        current.x--;
						current.grid_path[current.y][current.x] = 1;
                        continue;
                    }
                }
                if (( current.y < max_x - 1) && ( current.grid_path[ current.y ][current.x + 1] == 0) ) {
                    if ( grid_data[current.y][current.x + 1] == next_symbol ) {
                        current.step++;
                        current.x++;
						current.grid_path[current.y][current.x] = 1;
                        continue;
                    }
                }

                break;
            }
            if (current.step == word.length() ) {
                return true;
            }

            possible_path_list.pop_front();
        }

        return false;
    }

private:
    map< char, vector<path> > m_startingPositions;
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

    Grid grid;

    while ( getline(inFile, inputLine)) {
        cout << (grid.findWord(inputLine) ? "True" : "False" ) << endl;
    }

    return 0;
}
