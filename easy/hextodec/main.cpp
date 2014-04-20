#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int getDec(const string &line) {
    int result = 0;

    for (size_t i=0; i < line.length(); i++) {
        result = result * 16;

        if (line[i] >= '0' && line[i] <= '9' ) {
            result += (line[i] - '0');
        } else {
            result += line[i] - 'a' + 10;
        }
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
        cout << getDec(inputLine) << endl;
    }

    return 0;
}
