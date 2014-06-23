#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int start(const string &line) {
    unsigned int candidate = line.length();

    for (size_t position=0; position < line.length(); position++) {
        if (line[position] == 'C') {
            return position;
        }
        if (line[position] == '_') {
            candidate = position;
        }
    }

    return candidate;
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

    if (!getline(inFile, inputLine)) {
        return 0;
    }

    unsigned int position = start(inputLine);
    unsigned int next_position;
    unsigned int i;
    char *data = const_cast<char*>(inputLine.c_str());
    data[position] = '|';
    cout << data << endl;

    while ( getline(inFile, inputLine)) {
        next_position = inputLine.length();
        for (i = (position == 0) ? 0 : position-1; i < position + 2 && i < inputLine.length(); i++) {
            if (inputLine[i] == 'C') {
                next_position = i;
                break;
            }

            if (inputLine[i] == '_') {
                next_position = i;
            }
        }

        if (next_position == inputLine.length()) {
            break;
        }

        char *data = const_cast<char*>(inputLine.c_str());

        if (next_position < position) {
            data[next_position] = '/';
        } else if (next_position > position) {
            data[next_position] = '\\';
        } else {
            data[next_position] = '|';
        }
        cout << data << endl;
        position = next_position;
    }

    return 0;
}
