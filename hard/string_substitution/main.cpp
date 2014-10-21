#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void processLine( const string &line) {
    size_t start = 0;
    size_t end = 0;

    while (line[end] != ';') {
        end++;
    }

    string target( line.substr(0, end) );

    start = end + 1;
    while (start < line.length() ) {
        end = start + 1;
        while (end < line.length() && line[end] != ',') {
            end++;
        }
        string pattern( line.substr(start, end - start) );
        start = end + 1;

        end = start + 1;
        while (end < line.length() && line[end] != ',') {
            end++;
        }
        string replacement( line.substr(start, end - start) );
        for (unsigned int i=0; i < replacement.length(); i++) {
            replacement[i] += 2;
        }
        start = end + 1;

        unsigned int position = 0;

        while ( (position = target.find(pattern, position) ) != string::npos ) {
            if ( position + pattern.length() > target.length()) {
                break;
            }
            target.replace( position, pattern.length(), replacement);
        }
    }

    for (unsigned int i=0; i < target.length(); i++) {
        if (target[i] > '1') {
            target[i] -= 2;
        }
    }

    cout << target << endl;
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
        processLine(inputLine);
    }

    return 0;
}
