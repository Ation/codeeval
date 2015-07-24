#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void swap_numbers(string &line) {
    char *str = const_cast<char*>(line.c_str());

    size_t word_start = 0;
    size_t word_end = 0;

    while (word_start < line.length()) {
        while(true) {
            if ((word_end == line.length()) || (str[word_end] == ' ')){
                word_end--;
                break;
            }
            word_end++;
        }

        char temp = str[word_start];
        str[word_start] = str[word_end];
        str[word_end] = temp;

        word_start = word_end + 2;
        word_end = word_start;
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
        swap_numbers(inputLine);
    }

    return 0;
}
