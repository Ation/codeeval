#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

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
        const char *data = inputLine.c_str();

        int  position = inputLine.length() - 1;
        char symbol = data[position];

        position -= 2;

        for (; position >= 0; position--) {
            if (data[position] == symbol) {
                break;
            }
        }

        cout << position << endl;
    }

    return 0;
}
