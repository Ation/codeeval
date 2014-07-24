#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printNextToLast(const string &line) {
    char *data = const_cast<char*>(line.c_str());

    // find last word
    size_t position = line.length() - 1;
    while (data[position] != ' ') {
        position--;
    }

    while (data[position] == ' ') {
        data[position] = 0;
        position--;
    }

    for (;;) {
        if (position == 0) {
            break;
        }
        position--;
        if (data[position] == ' ') {
            position ++;
            break;
        }
    }

    cout << (&data[position]) << endl;
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
        printNextToLast(inputLine);
    }

    return 0;
}
