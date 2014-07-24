#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printMissing(const string &line) {
    vector<bool> symbols;
    int used = 0;
    int index;
    char temp;

    symbols.resize(26, false);

    for (size_t i=0; i < line.length(); i++) {
        temp = line[i];

        if (temp >= 'a' && temp <= 'z') {
            index = temp - 'a';
        } else if (temp >= 'A' && temp <= 'Z') {
            index = temp - 'A';
        } else {
            continue;
        }

        if (!symbols[index]) {
            used++;
            symbols[index] = true;
        }
    }

    if (used == 26) {
        cout << "NULL" << endl;
    } else {
        for (size_t i=0; i < symbols.size(); i++) {
            if (!symbols[i]) {
                cout << (char)(i + 'a');
            }
        }
        cout << endl;
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
        printMissing(inputLine);
    }

    return 0;
}
