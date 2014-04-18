#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

bool compareString(const string &line, size_t secondStart, size_t compareStart) {
    bool result = true;
    size_t i;
    for (i=0; i < line.length() - compareStart; i++) {
        if (line[i] != line[i + compareStart]) {
            result = false;
            break;
        }
    }

    if (result) {
        for (size_t j=secondStart; j < compareStart; i++, j++) {
            if (line[i] != line[j]) {
                result = false;
                break;
            }
        }
    }

    return result;
}

bool containRotation(const string &line) {
    size_t comaPosition = 0;
    char firstSymbol = line[0];

    bool result = false;

    for (comaPosition = 0; comaPosition < line.length() && line[comaPosition] != ','; comaPosition++) {
    }

    size_t  secondStart = comaPosition + 1;

    for (size_t i = secondStart; i < line.length(); i++) {
        if ( compareString(line, secondStart, i) ) {
            result = true;
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
        cout << (containRotation(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
