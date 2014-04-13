#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
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

    int numberCount[10];
    int current;

    bool    self_describing;

    while ( getline(inFile, inputLine)) {
        memset(numberCount, 0, 10 * sizeof(int));
        self_describing = true;

        for (unsigned int i=0; i < inputLine.length(); i++) {
            numberCount[ inputLine[i] - '0'] ++;
        }

        for (unsigned int i=0; i < inputLine.length(); i++) {
            current = inputLine[i] - '0';
            if ( numberCount[i] != current) {
                self_describing = false;
                break;
            } 
        }

        cout << ( self_describing ? "1" : "0" ) << endl;
    }

    return 0;
}
