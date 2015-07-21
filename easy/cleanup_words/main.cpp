#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void cleanup_words(const string &line) {
    char *str = const_cast<char*>(line.c_str());
    char *current = str;
    char *insert = str;
    bool first = true;
    bool space_required = false;

    while (*current) {
        char c = *current;
        if ( (c >= 'a') && (c <= 'z')) {
            if (space_required && !first) {
                *insert++ = ' ';
                space_required = false;
            }
            *insert++ = c;
            first = false;
        } else if ( (c >= 'A') && (c <= 'Z')) {
            if (space_required && !first) {
                *insert++ = ' ';
                space_required = false;
            }
            *insert++ = c + 32;
            first = false;
        } else {
            space_required = !first;
        }

        ++current;
    }
    *insert = 0;

    cout << str << endl;
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
        cleanup_words(inputLine);
    }

    return 0;
}
