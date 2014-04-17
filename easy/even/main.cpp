#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int getInteger(const string &line) {
    int result = 0;

    for (size_t position = 0; position < line.length(); position++) {
        result = result * 10 + (line[position] - '0');
    }

    return result;
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
        int number = getInteger(inputLine);

        cout << ( number & 1 ? 0 : 1) << endl;
    }

    return 0;
}
