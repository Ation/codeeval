#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void print_unique(string &line) {
    unsigned int start = 0;
    unsigned int i = 0;
    unsigned int end = 1;

    while (end < line.length() ) {
        if ( line[start] == line[end] ) {
            end++;
        } else {
            line[i] = line[start];
            i++;
            start = end;
            end++;
        }
    }
    line[i] = line[start];

    line.resize(i + 1);

    cout << line << endl;
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
        print_unique( inputLine );
    }

    return 0;
}
