#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

static const string none_string = "NONE";

bool is_all_spaces(const char *str, unsigned int start, unsigned int length) {
    for (unsigned int i = start; i < start + length; i++) {
        if (str[i] != ' ') {
            return false;
        }
    }

    return true;
}

bool are_equal(const char *str, unsigned int first_start, unsigned int second_start, unsigned int length) {
    for (unsigned int i=0; i < length; i++) {
        if (str[first_start + i] != str[second_start + i]) {
            return false;
        }
    }

    return true;
}

void print_substring(const string &line) {
    unsigned int line_length = line.length();
    unsigned int sub_length = line_length / 2;
    const char *str = line.c_str();

    while ( sub_length != 0) {
        // loop from start
        for ( unsigned int source_start = 0; source_start <= line_length - (sub_length << 1); source_start++) {
            // check string
            if (!is_all_spaces(str, source_start, sub_length)) {
                // loop to end
                for (unsigned int test_start = source_start + sub_length; test_start <= line_length - sub_length; test_start++) {
                    if ( are_equal(str, source_start, test_start, sub_length) ) {
                        // print
                        cout << line.substr(source_start, sub_length) << endl;
                        return;
                    }
                }
            }
        }
        sub_length--;
    }

    cout << none_string << endl;
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
        print_substring(inputLine);
    }

    return 0;
}
