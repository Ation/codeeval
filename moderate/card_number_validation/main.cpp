#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

static const int _summ[] = {2, 4, 6, 8, 1, 3, 5, 7, 9};

bool validateCard( const string &line ) {
    unsigned int check_sum = 0;
    unsigned int counter = 0;

    unsigned int digit;

    for (int i = line.length() - 1; i >= 0; i--) {
        if ( line[i] == ' ') {
            continue;
        }

        digit = line[i] - '0';
        if (digit != 0) {
            if ( counter % 2 == 0 ) {
                check_sum += digit;
            } else {
                check_sum += _summ[ digit - 1];
            }
        }
        counter++;
    }

    return ( check_sum % 10 == 0);
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
        cout << ( validateCard(inputLine) ? 1 : 0) << endl;
    }

    return 0;
}
