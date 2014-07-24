#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int getRomanArabic(const string &line) {
    int result = 0;
    unsigned int lastRoman = 0;
    unsigned int currentRoman;
    unsigned int arabic;

    for (int i = line.length() - 1; i >= 1; i -= 2) {
        switch(line[i]) {
        case 'I':
            currentRoman = 1;
            break;
        case 'V':
            currentRoman = 5;
            break;
        case 'X':
            currentRoman = 10;
            break;
        case 'L':
            currentRoman = 50;
            break;
        case 'C':
            currentRoman = 100;
            break;
        case 'D':
            currentRoman = 500;
            break;
        case 'M':
            currentRoman = 1000;
            break;
        }

        arabic = line[i-1] - '0';
        if (lastRoman > currentRoman) {
            result -= arabic * currentRoman;
        } else {
            result += arabic * currentRoman;
        }

        lastRoman = currentRoman;
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
        cout << getRomanArabic(inputLine) << endl;
    }

    return 0;
}
