#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool getDouble(const string &line, size_t &position, double &number) {
    bool negative = false;
    double result = 0;
    char symbol;
    // find start
    for (; position < line.length(); position++ ) {
        symbol = line[position];
        if (symbol == '-') {
            negative = true;
            position++;
            break;
        }
        if (symbol >= '0' && symbol <= '9') {
            break;
        }
    }

    if (position == line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        symbol = line[position];
        if (symbol == '.') {
            int devider = 10;

            // after dot
            position++;
            for (; position < line.length(); position++) {
                symbol = line[position];
                if (symbol >= '0' && symbol <= '9') {
                    result = result + ((double)(symbol - '0')) / devider;
                    devider *= 10;
                } else {
                    break;
                }
            }
            break;
        } else if (symbol >= '0' && symbol <= '9') {
            result = result * 10 + (symbol - '0');
        } else {
            break;
        }
    }

    if (negative) {
        result = -result;
    }

    number = result;
    return true;
}

void printFraction( unsigned int number, char symbol) {
    if (number < 10) {
        cout << '0';
    }
    cout << number << symbol;
}

void print_angle(const string &line) {
    size_t position = 0;
    double angle;
    getDouble( line, position, angle);
    int toPrint = 0;

    toPrint = (int)angle;
    cout << toPrint << '.';

    angle = ( angle - toPrint) * 60;
    toPrint = (int)angle;
    printFraction( toPrint, '\'');

    angle = ( angle - toPrint) * 60;
    toPrint = (int)angle;
    printFraction( toPrint, '\"');

    cout << endl;
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
        print_angle(inputLine);
    }

    return 0;
}
