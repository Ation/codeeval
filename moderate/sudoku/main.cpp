#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int getDigit(const string &line, size_t &position) {
    int result = line[position] - '0';
    position += 2;

    return result;
}

const int position_mask[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

bool isCorrectSudoku(const string &line) {
    size_t position = 0;

    int vertical_mask[9];
    int horizontal_mask[9];
    int subgrid_mask[9];


    int size = getDigit(line, position);

    int subgridSize = size == 4 ? 2 : 3;

    int digit;
    memset(vertical_mask, 0, size * sizeof(int));
    memset(horizontal_mask, 0, size * sizeof(int));
    memset(subgrid_mask, 0, size * sizeof(int));

    bool    result = true;

    for (int i=0; (i < size) && result; i++) {
        for (int j=0; j < size; j++) {
            digit = getDigit(line, position);
            if (digit > size) {
                result = false;
                break;
            }

            int subgridIndex = (i/subgridSize) * subgridSize + ( j / subgridSize);

            if (horizontal_mask[j] & position_mask[digit]) {
                result = false;
                break;
            }

            if (vertical_mask[i] & position_mask[digit]) {
                result = false;
                break;
            }

            if (subgrid_mask[subgridIndex] & position_mask[digit]) {
                result = false;
                break;
            }

            vertical_mask[i] |= position_mask[digit];
            horizontal_mask[j] |= position_mask[digit];
            subgrid_mask[subgridIndex] |= position_mask[digit];
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        cout << (isCorrectSudoku(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
