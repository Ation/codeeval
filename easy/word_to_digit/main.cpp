#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void wordToDigit(const string &line) {
    size_t position = 0;

    while (position < line.length()) {
        switch (line[position]) {
        case 'z':
            cout << '0';
            position += 5;
            break;
        case 'o':
            cout << '1';
            position += 4;
            break;
        case 't':
            switch(line[position + 1]) {
            case 'w':
                cout << '2';
                position += 4;
                break;
            case 'h':
                cout << '3';
                position += 6;
                break;
            }
            break;
        case 'f':
            switch(line[position + 1]) {
            case 'o':
                cout << '4';
                break;
            case 'i':
                cout << '5';
                break;
            }
            position += 5;
            break;
        case 's':
            switch(line[position + 1]) {
            case 'i':
                cout << '6';
                position += 4;
                break;
            case 'e':
                cout << '7';
                position += 6;
                break;
            }
            break;
        case 'e':
            cout << '8';
            position += 6;
            break;
        case 'n':
            cout << '9';
            position += 5;
            break;
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
        wordToDigit(inputLine);
    }

    return 0;
}
