#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getWordLength(string &line, unsigned int &start) {
    char *str = const_cast<char*>(line.c_str());
    unsigned int result = 0;

    for (; start < line.length(); start++) {
        if (str[start] == ' ') {
            str[start] = 0;
            start++;
            break;
        }
        result ++;
    }

    for (; start < line.length(); start++) {
        if (str[start] != ' ') {
            break;
        }
    }

    return result;
}

void printLongestWord(string &line) {
    unsigned int current_length = 0;
    unsigned int max_length = 0;

    unsigned int current_start = 0;
    unsigned int max_start = 0;

    unsigned int i = 0;

    while ( i < line.length()) {
        current_start = i;
        current_length = getWordLength(line, i);

        if (current_length > max_length) {
            max_length = current_length;
            max_start = current_start;
        }
    }

    cout << (&line[max_start]) << endl;
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
        printLongestWord(inputLine);
    }

    return 0;
}
