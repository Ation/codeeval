#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

unsigned int getInteger(const string &line) {
    unsigned int result = 0;

    for (size_t i=0; i < line.length(); i++) {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}

unsigned int getSquareCount(const string &line) {
    unsigned int count = 0;

    const unsigned int sum = getInteger(line);
    if (sum <= 2) {
        return 1;
    }

    unsigned int y = (unsigned int)(sqrt(sum) + 1);
    unsigned int yy = y * y;

    unsigned int x = 0;
    unsigned int current;

    while (x < y) {
        current = x * x + yy;
        if (current == sum) {
            ++x;
            --y;
            yy = y * y;
            count++;
        } else if (current > sum) {
            --y;
            yy = y * y;
        } else {
            ++x;
        }
    }

    return count;
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

    getline(inFile, inputLine);
    int test_cases = getInteger(inputLine);

    for (int i=0; i < test_cases; ++i) {
        getline(inFile, inputLine);
        cout << getSquareCount(inputLine) << endl;
    }

    while ( getline(inFile, inputLine)) {
        cout << getSquareCount(inputLine) << endl;
    }

    return 0;
}
