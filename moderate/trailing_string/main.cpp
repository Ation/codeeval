#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int haveTrailing(const string &line) {
    int result = 1;

    size_t coma_position = line.length() - 1;

    while (line[coma_position] != ',' && coma_position > 0) {
        coma_position--;
    }

    if (line.length() - 1 - coma_position > coma_position) {
        return 0;
    }

    for (size_t i = coma_position - 1, j = line.length() - 1; j > coma_position; i--, j--) {
        if (line[i] != line[j] ) {
            result = 0;
            break;
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
        cout << haveTrailing(inputLine) << endl;
    }

    return 0;
}
