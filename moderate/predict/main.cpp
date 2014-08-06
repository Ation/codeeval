#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstdint>

using namespace std;

uint32_t getUnsignedInteger(const string &line) {
    uint32_t result = 0;
    size_t position = 0;
    char temp;
    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            break;
        }
    }

    return result;
}

uint32_t lower_power2( uint32_t value) {
    value = value | (value >> 1);
    value = value | (value >> 2);
    value = value | (value >> 4);
    value = value | (value >> 8);
    value = value | (value >> 16);
    return value - ( value >> 1);
}

uint32_t prediction( const string &line) {
    uint32_t number = getUnsignedInteger( line );
    uint32_t result = 1;

    if (number < 2) {
        return number;
    }

    uint32_t lower = lower_power2( number );
    uint32_t shift = lower >> 1;

    while (lower + 1 < number) {
        if ( number >= lower + shift) {
            lower += shift;
            result++;
        }
        shift >>= 1;
    }

    return ( result + (number & 1)) % 3;
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
        cout << prediction( inputLine ) << endl;
    }

    return 0;
}
