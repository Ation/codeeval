#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

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

void decode( string &line) {
    unsigned int temp;
    unsigned int min;
    unsigned int diff;

    vector<unsigned int> numbers;
    size_t position = 0;

    getUnsignedInteger(line, position, temp);
    getUnsignedInteger( line, position, temp);

    min = temp;
    numbers.push_back(temp);

    while ( getUnsignedInteger(line, position, temp) ) {
        numbers.push_back(temp);
        if (temp < min) {
            min = temp;
        }
    }

    diff = min - 32;

    string result(numbers.size(), ' ');
    for (unsigned int i=0; i < numbers.size(); i++) {
        result[i] = numbers[i] - diff;
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
        decode(inputLine);
    }

    return 0;
}
