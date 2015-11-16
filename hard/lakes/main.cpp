#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

class LakesCounter {
public:
    LakesCounter(){}

    uint count_lakes(const string& line) {
        size_x = 0;
        size_y = 0;
        size_t position = 0;
        while (position < line.length()) {
            if (line[position] == 'o') {
                lakes_map[size_y][size_x] = 1;
                ++size_x;
            } else if (line[position] == '#') {
                lakes_map[size_y][size_x] = 0;
                ++size_x;
            } else if (line[position] == '|') {
                size_x = 0;
                ++size_y;
            }
            ++position;
        }
        ++size_y;

        uint result = 0;

        for ( uint x=0; x < size_x; ++x) {
            for (uint y=0; y < size_y; ++y) {
                if (lakes_map[y][x]) {
                    ++result;
                    lakes_map[y][x] = 0;

                    process_connected_lakes(y, x);
                }
            }
        }

        return result;
    }

private:
    char lakes_map[30][30];
    uint size_x;
    uint size_y;

    void process_connected_lakes(uint center_y, uint center_x) {
        uint start_x = (center_x == 0 ? 0 : center_x - 1);
        uint end_x = center_x + 1 == size_x ? center_x : center_x + 1;

        uint start_y = (center_y == 0 ? 0 : center_y - 1);
        uint end_y = center_y + 1 == size_y ? center_y : center_y + 1;

        for (uint y = start_y; y <= end_y; ++y) {
            for (uint x = start_x; x <= end_x; ++x) {
                if (lakes_map[y][x]) {
                    lakes_map[y][x] = 0;
                    process_connected_lakes(y, x);
                }
            }
        }
    }
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

    LakesCounter lc;

    while ( getline(inFile, inputLine)) {
        cout << lc.count_lakes(inputLine) << endl;
    }

    return 0;
}
