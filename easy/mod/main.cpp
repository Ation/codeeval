#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int getInteger(const string &line, size_t &position) {
    int result = 0;

    while (position < line.length()) {
        if (line[position] == ',') {
            position++;
            break;
        }
        result = result * 10 + (line[position] - '0');

        position++;
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
        size_t position = 0;
        int first = getInteger(inputLine, position);
        int second = getInteger(inputLine, position);

        int result = first / second;
        result = first - (result * second);

        cout << result << endl;
    }

    return 0;
}
