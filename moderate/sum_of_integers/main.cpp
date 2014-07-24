#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;


bool getInteger(const string &line, size_t &position, int &integer) {
    int result = 0;
    bool negative = false;
    char temp;

    do {
        if (position == line.length()) {
            return false;
        }
        temp = line[position];
        if (temp == '-') {
            negative = true;
            position++;
            break;
        }
        if (temp >= '0' && temp <= '9') {
            break;
        }
        position++;
    } while (true);

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position++;
            break;
        }
    }

    if (negative) {
        if (result == 0) {
            return false;
        }
        result = -result;
    }

    integer = result;
    return true;
}

void printLargestSum(const string &line) {
    size_t position = 0;
    int result;
    int current_sum;

    int number;

    getInteger(line, position, number);

    result = number;
    current_sum = number;

    while ( getInteger(line, position, number) ) {
        current_sum += number;
        if (current_sum < number) {
            current_sum = number;
        }

        if (result < current_sum) {
            result = current_sum;
        }
    }

    cout << result << endl;

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
        printLargestSum(inputLine);
    }

    return 0;
}
