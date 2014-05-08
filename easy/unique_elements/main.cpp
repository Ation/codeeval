#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printUnique(const string &line) {
    size_t cursor = 0;
    size_t  last_start = 0;
    size_t  last_length = 0;

    char symbol;

    // get first and print it
    while ( cursor < line.length()) {
        symbol = line[cursor];
        cursor++;
        if ( symbol == ',') {
            break;
        }
        cout << symbol;
    }
    last_length = cursor - 1;

    // iterate through others
    while (cursor < line.length() ) {
        bool differ = false;

        size_t current_start = cursor;
        size_t current_length = 0;

        while (cursor + current_length < line.length()) {
            symbol = line[cursor + current_length];
            if (symbol == ',') {
                break;
            }
            if (line[last_start + current_length] != symbol) {
                differ = true;
                break;
            }
            current_length++;
        }

        if (differ || (last_length != current_length) ) {
            // print next
            cout << ',';
            last_start = cursor;
            while (cursor < line.length()) {
                symbol = line[cursor];
                cursor++;
                if (symbol == ',') {
                    break;
                }
                cout << symbol;
            }
            last_length = cursor - last_start - 1;
        } else {
            cursor += (current_length + 1);
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
        printUnique(inputLine);
    }

    return 0;
}
