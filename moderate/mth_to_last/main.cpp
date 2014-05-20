#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    unsigned int result = 0;
    char temp;
    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    return result;
}

void printMth(const string &line) {
    size_t start_position = line.length() - 1;
    size_t position;

    while (line[start_position] != ' ') {
        start_position--;
    }

    position = start_position + 1;
    start_position--;

    unsigned int m = getUnsignedInteger(line, position);
    int index = start_position - (m - 1) * 2;
    if (index >= 0) {
        cout << line[start_position - (m - 1) * 2] << endl;
    }
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
        printMth(inputLine);
    }

    return 0;
}
