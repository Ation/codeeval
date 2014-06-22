#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int readLength(const string &line, size_t &position) {
    unsigned int result = 0;

    for (; position < line.length() && line[position] != '0'; position++) {
    }

    for (; position < line.length() && line[position] == '0'; position++, result++) {
    }

    return result;
}

bool readFlag(const string &line, size_t &position) {
    unsigned int length = readLength(line, position);

    return (length == 2);
}

void printNumber(const string &line) {
    size_t position = 0;
    unsigned int result = 0;

    bool toOnes;
    unsigned int length;

    while (position < line.length()) {
        toOnes = readFlag(line, position);
        length = readLength(line, position);

        if (toOnes) {
            result += 1;
            result <<= length;
            result -= 1;
        } else {
            result <<= length;
        }
    }

    cout << result << endl;
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
        printNumber(inputLine);
    }

    return 0;
}
