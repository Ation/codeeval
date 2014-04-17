#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int getIndex(char symbol) {
    if (symbol >= 'a' && symbol <= 'z') {
        return symbol - 'a';
    } else if (symbol >= 'A' && symbol <= 'Z') {
        return symbol - 'A' + 26;
    } else if (symbol >= '0' && symbol <= '9') {
        return symbol + 52 - '0';
    } else if (symbol == ' ') {
        return 62;
    } else {
        return -1;
    }
}

bool containRotation(const string &line) {
    const size_t  size = 63;
    int counter[size];
    char symbol;
    int index;
    bool result = true;
    memset(counter, 0, sizeof(int) * size);

    size_t i=0;
    for (i=0; i < line.length(); i++) {
        symbol = line[i];

        index = getIndex(symbol);
        if (index == -1) {
            i++;
            break;
        }
        counter[index]++;
    }

    if (line.length() - i != i - 1) {
        result = false;
    } else  for (; i < line.length(); i++) {
        symbol = line[i];

        index = getIndex(symbol);
        if (index == -1) {
            i++;
            break;
        }
        counter[index]--;
        if (counter[index] < 0) {
            result = false;
            break;
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
        cout << (containRotation(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
