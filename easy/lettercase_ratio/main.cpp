#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printRatio(const string &line) {
    int total = 0;
    int lower = 0;
    int upper = 0;

    char symbol;

    for (size_t i = 0; i < line.length(); i++) {
        symbol = line[i];

        if (symbol >= 'a' && symbol <= 'z') {
            lower++;
        } else if (symbol >= 'A' && symbol <= 'Z') {
            upper++;
        }
    }

    total = lower + upper;

    float lower_ratio = (double)(lower * 100) / total;
    float upper_ratio = (double)(upper * 100) / total;

    cout << "lowercase: " << lower_ratio << " uppercase: " << upper_ratio << endl;
}

int main(int argc, char *argv[]) {
    cout.precision(2);
    cout << fixed ;

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        printRatio(inputLine);
    }

    return 0;
}
