#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getUnsgined(const string &line, size_t start, size_t length) {
    unsigned int result = 0;

    for (size_t i=0; i < length; i++) {
        result = result*10 + (line[start + i] - '0');
    }

    return result;
}

void splitTheNumber(const string &line) {
    bool plus = false;

    size_t length1;
    size_t length2;

    size_t position;

    int left;
    int right;

    for (position = 0; line[position] != ' '; position++) {
    }

    length2 = position;
    while (line[position] == ' ') {
        position++;
    }

    for (length1 = 0; line[position + length1] != '+' && line[position + length1] != '-'; length1++) {
    }

    plus = line[position + length1] == '+';
    length2 -= length1;

    left = getUnsgined(line, 0, length1);
    right = getUnsgined(line, length1, length2);

    cout << (plus ? left + right : left - right) << endl;
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
        splitTheNumber(inputLine);
    }

    return 0;
}
