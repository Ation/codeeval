#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    vector<int> symbols;

    symbols.resize(26, 0);

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        for (int i=0; i < inputLine.length(); i++) {
            char s = inputLine[i];

            if (( s >= 'A') && (s <= 'Z')) {
                s += 32;                
            }

            if ((s >= 'a') && (s <= 'z')) {
                symbols[s - 'a']++;
            }
        }

        sort(symbols.begin(), symbols.end());

        int sum = 0;
        for (int i = 26; i > 0 ; i--) {
            if (symbols[i-1] == 0) {
                break;
            }

            sum += i * symbols[i-1];
            symbols[i-1] = 0;
        }

        cout << sum << endl;
    }

    return 0;
}
