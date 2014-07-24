#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

bool getUnsignedInteger(const string &line, size_t &position, unsigned int &number) {
    unsigned int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

    if (position >= line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

void printMultiply(const string &line) {
    unsigned int target;
    unsigned int number;
    unsigned int result;
    size_t position = 0;

    getUnsignedInteger(line, position, target);
    getUnsignedInteger(line, position, number);

    result = number;

    while (result < target) {
        result += number;
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
        printMultiply(inputLine);
    }

    return 0;
}
