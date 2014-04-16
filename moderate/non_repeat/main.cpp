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

    const int size = 26;
    char table[size];

    while ( getline(inFile, inputLine)) {
        memset(table, 0, size);

        const char* data = inputLine.c_str();

        size_t i;
        for (i=0; i < inputLine.length(); i++) {
            table[ data[i] - 'a']++;
        }

        for (i=0; i < inputLine.length(); i++) {
            if ( table[ data[i] - 'a'] == 1) {
                break;
            }
        }

        cout << data[i] << endl;

    }

    return 0;
}
