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

    unsigned int limit = sqrt(sum) + 1;

    for (unsigned int x=0; x < limit; x++) {
        double y = sqrt(sum - x*x);

        if (y < x) {
            break;
        }

        if (y == (int)y) {
            count++;
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

    while ( getline(inFile, inputLine)) {
        cout << getSquareCount(inputLine) << endl;
    }

    return 0;
}
