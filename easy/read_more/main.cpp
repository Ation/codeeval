#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void read_more(const string &line) {
    if (line.length() <= 55) {
        cout << line << endl;
    } else {
        unsigned int length = 39;
        while ( (line[length] != ' ') && (length != 0) ) {
            length--;
        }
        if (line[length] == ' ') {
            while ( (line[length] == ' ') && (length != 0) ) {
                length--;
            }
        } else {
            length = 39;
        }

        cout << line.substr(0, length + 1) << "... <Read More>" << endl;
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
        read_more(inputLine);
    }

    return 0;
}
