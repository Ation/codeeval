#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getInteger(const string &line) {
    unsigned int result = 0;

    for (size_t i = 0 ; i < line.length(); ++i) {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}

unsigned long long getFibonacci(const string &line) {
    unsigned int index = getInteger(line);
    unsigned long long number = 0;

    unsigned long long left;
    unsigned long long right;

    if (index == 0) {
        return 0;
    }

    if (index < 3) {
        return 1;
    }

    left = 1;
    right = 1;
    number = 2;

    for (unsigned int i=2; i < index; i++) {
        number = left + right;
        left = right;
        right = number;
    }

    return number;
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
        cout << getFibonacci(inputLine) << endl;
    }

    return 0;
}
