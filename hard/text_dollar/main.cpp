#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    unsigned int result = 0;
    char temp;
    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    return result;
}

static const string hundred = "Hundred";
static const string thousand = "Thousand";
static const string million = "Million";

static const string digits[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

static const string special[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

static const string decades[] = {"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

void printAmount(unsigned int value) {
    if (value < 10) {
        cout << digits[value - 1];
    } else if (value >= 20) {
        unsigned int decade = (value / 10) - 2;
        unsigned int digit = value % 10;

        cout << decades[decade];
        if (digit != 0) {
            cout << digits[digit - 1];
        }
    } else {
        cout << special[value - 10];
    }
}

void printDollars(const string &line) {
    size_t position = 0;
    unsigned int value = getUnsignedInteger(line, position);

    if (value >= 1000000) {
        printAmount(value / 1000000);
        value %= 1000000;
        cout << million;
    }

    if (value > 1000) {
        printAmount(value / 1000);
        value %= 1000;
        cout << thousand;
    }

    if (value > 100) {
        printAmount(value / 100);
        value %= 100;
        cout << hundred;
    }

    printAmount(value);

    cout << "Dollars" << endl;

    return;
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
        printDollars(inputLine);
    }

    return 0;
}
