#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdint.h>

using namespace std;

unsigned int get_code(const char symbol, bool with_dot) {
    unsigned int result;

    switch(symbol) {
    case '1':
        result = 0x30;
        break;
    case '2':
        result = 0x6D;
        break;
    case '3':
        result = 0x79;
        break;
    case '4':
        result = 0x33;
        break;
    case '5':
        result = 0x5B;
        break;
    case '6':
        result = 0x5F;
        break;
    case '7':
        result = 0x70;
        break;
    case '8':
        result = 0x7F;
        break;
    case '9':
        result = 0x7B;
        break;
    case '0':
        result = 0x7E;
        break;
    }

    result <<= 1;

    if (with_dot) {
        result |= 1;
    }

    return result;
}

vector<unsigned int> what_to_display( const string &line, const size_t start_position) {
    vector<unsigned int> result;

    for ( size_t i=start_position; i < line.length(); ++i) {
        bool with_dot = false;
        if ( i + 1 < line.length() ) {
            if (line[i+1] == '.') {
                with_dot = true;
            }
        }

        result.push_back( get_code(line[i], with_dot) );

        if (with_dot) {
            ++i;
        }
    }

    return result;
}

unsigned int read_digit(const string &line, size_t start_position) {
    unsigned int result = 0;

    for (size_t i=0; i < 8; ++i) {
        result <<= 1;
        if (line[i + start_position] == '1') {
            result |= 1;
        }
    }

    return result;
}

bool can_display_all( const string &inputLine) {
    unsigned int digits[12];
    size_t start_position = 0;

    for (unsigned int i=0; i < 12; ++i) {
        digits[i] = read_digit( inputLine, start_position);
        start_position += 9;
    }

    auto to_display =  what_to_display(inputLine, start_position);

    bool result;

    for (unsigned int i=0; i <= 12 - to_display.size(); ++i) {
        result = true;
        for (unsigned int j=0; j < to_display.size(); ++j) {
            if ( to_display[j] != ( to_display[j] & digits[i + j]) ) {
                result = false;
                break;
            }
        }
        if (result) {
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
        cout << ( can_display_all(inputLine) ? 1 : 0) << endl;
    }

    return 0;
}