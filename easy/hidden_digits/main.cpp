#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printHiddenDigits(const string &line) {
    bool printed = false;
    char temp;

    for (size_t i=0; i < line.length(); i++) {
        temp = line[i];
        if (temp >= 'a' && (temp <= 'j')) {
            cout << (char)(temp - 49);
            printed = true;
        } else if (temp >= '0' && temp <= '9') {
            cout << temp;
            printed = true;
        }
    }

    if (!printed) {
        cout << "NONE" << endl;
    } else {
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
        printHiddenDigits(inputLine);
    }

    return 0;
}
