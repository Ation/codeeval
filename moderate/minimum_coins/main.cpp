#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int getInteger(const string &line) {
    int result = 0;

    for (size_t i = 0; i < line.length(); i++) {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}

int getNumberOfCoins(const string &line) {
    int target = getInteger(line);

    int result = 0;

    result += target / 5;
    target %= 5;

    result += target / 3;
    target %= 3;

    result += target;

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
        cout << getNumberOfCoins(inputLine) << endl;
    }

    return 0;
}
