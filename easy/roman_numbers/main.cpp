#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef struct __numberSet {
    char one;
    char five;
} NumberSet;

void printRoman(const string &line) {
    static const NumberSet numbers[] = { {'I', 'V'}, {'X', 'L'}, {'C', 'D'}, {'M', 0}, {0, 0}};
    int offset = 11;
    char str[13];

    str[12] = 0;

    int rank = 0;
    int digit;
    for (int i=line.length() - 1; i >= 0; i--, rank++) {
        digit = line[i] - '0';

        switch (digit) {
        case 9:
            str[offset] = numbers[rank+1].one;
            str[offset-1] = numbers[rank].one;
            offset -= 2;
            break;
        case 4:
            str[offset] = numbers[rank].five;
            str[offset-1] = numbers[rank].one;
            offset -= 2;
            break;
        case 8:
            str[offset] = numbers[rank].one;
            offset--;
        case 7:
            str[offset] = numbers[rank].one;
            offset--;
        case 6:
            str[offset] = numbers[rank].one;
            offset--;
        case 5:
            str[offset] = numbers[rank].five;
            offset--;
            break;
        case 3:
            str[offset] = numbers[rank].one;
            offset--;
        case 2:
            str[offset] = numbers[rank].one;
            offset--;
        case 1:
            str[offset] = numbers[rank].one;
            offset--;
            break;
        case 0:
            break;
        }
    }

    cout << &(str[offset+1]) << endl;
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
        if (inputLine.length() == 0) {
            break;
        }
        printRoman(inputLine);
    }

    return 0;
}
