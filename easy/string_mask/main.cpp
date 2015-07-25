#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void transfomr_string(string& line) {
    size_t word_start = 0;
    size_t mask_start = 2;

    char *str = const_cast<char*>(line.c_str());

    while (mask_start) {
        if ((line[mask_start] == '1') || (line[mask_start] == '0')) {
            break;
        }
        mask_start++;
    }

    for (size_t i=0; mask_start + 1 < line.length(); ++i) {
        if ( str[i] == ' ' ) {
            str[i] = 0;
            break;
        }

        if (str[mask_start + i] == '1') {
            str[i] -= 32;
        }
    }
    cout << str << endl;
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
        transfomr_string(inputLine);
    }

    return 0;
}
