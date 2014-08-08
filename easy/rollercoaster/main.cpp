#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool isAlpha(char c) {
    return ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') );
}

char toLow(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 0x20;
    }
    return c;
}

char toUp(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 0x20;
    }
    return c;
}

void roll( string &line) {
    int index = 0;

    char (*rollers[2])(char) = {toUp, toLow};

    for (unsigned int i=0; i < line.length(); i++) {
        if ( isAlpha(line[i]) ) {
            line[i] = rollers[index](line[i]);
            index ^= 1;
        }
    }
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
        roll(inputLine);
        cout << inputLine << endl;
    }

    return 0;
}
