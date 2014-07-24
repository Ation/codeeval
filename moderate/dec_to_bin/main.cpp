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

void printBin(const string &line) {
    size_t position = 0;
    unsigned int number = getUnsignedInteger(line, position);
    unsigned int mask = 0x80000000;

    if (number == 0) {
        cout << '0' << endl;
        return;
    }

    while ( ! (number & mask) ) {
        mask >>= 1;
    }

    cout << '1';
    mask >>=1;

    while (mask) {
        if (number & mask) {
            cout << '1';
        } else {
            cout << '0';
        }
        mask >>= 1;
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
        printBin(inputLine);
    }

    return 0;
}
