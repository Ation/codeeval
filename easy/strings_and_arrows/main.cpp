#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

unsigned int count_arrows( const string &line) {
    size_t position = 0;
    unsigned int count = 0;

    string left_arrow = "<--<<";
    string right_arrow = ">>-->";

    const int arrow_length = left_arrow.length();

    for (size_t position = 0; position < line.length() - arrow_length + 1; ) {
        string *ref;
        if (line[position] == '<') {
            ref = &left_arrow;
        } else if (line[position] == '>') {
            ref = &right_arrow;
        } else {
            position++;
            continue;
        }

        bool arrow_detected = true;
        for (unsigned int i=0; i < arrow_length; ++i) {
            if ((*ref)[i] != line[position + i]) {
                arrow_detected = false;
                break;
            }
        }

        if (arrow_detected) {
            position += arrow_length - 1;
            count ++;
        } else {
            position++;
        }
    }

    return count;
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
        cout << count_arrows(inputLine) << endl;
    }

    return 0;
}
