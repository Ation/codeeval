#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int readInt(const string &line, size_t &position, int length) {
    int result = 0;

    for (int i=0; i < length; i++) {
        result <<= 1;
        result += line[position + i] - '0';
    }

    position += length;

    return result;
}

void decode(const string &line) {
    vector < vector <char> > symbols;

    size_t position = 0;
    int length = 1;
    int index = 0;
    int stop_index;

    symbols.emplace_back();

    for (; line[position] != '0' && line[position] != '1'; position++) {
        if (index == ( 1 << length) - 1) {
            // add new length
            symbols.emplace_back();
            index = 0;
            length++;
        }
        symbols[length - 1].emplace_back( line[position] );
        index++;
    }

    while ( (length = readInt(line, position, 3)) != 0) {
        stop_index = (1 << length) - 1;
        while ( (index = readInt( line, position, length) ) != stop_index ) {
            cout << symbols[length - 1][index];
        }
    }
    cout << endl;
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
        decode(inputLine);
    }

    return 0;
}
