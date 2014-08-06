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

void printNext( string &line) {
    unsigned int start = line.length() - 1;

    while (line[start] == '0') {
        --start;
    }

    unsigned int i = start;
    for ( ; i > 0; --i) {
        if (line[i] > line[i - 1]) {
            while (line[start] <= line[i-1]) {
                --start;
            }

            char temp = line[start];
            line[start] = line[i-1];
            line[i-1] = temp;

            sort(line.begin() + i, line.end());
            break;
        }
    }

    if (i == 0) {
        // insert 0
        char temp = line[0];
        line[0] = line[start];
        line[start] = temp;
        line.insert(line.begin() + 1, '0');
        sort(line.begin() + 1, line.end());
    }

    cout << line << endl;
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
        printNext(inputLine);
    }

    return 0;
}
