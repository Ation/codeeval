#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(/*parameters*/);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(/* parameters*/) {
        (this->*m_printer)(/*parameters*/);
    }
private:
    printerFunction m_printer;

    void firstPrinter(/* parameters*/) {
        m_printer = &Printer::nextPrinter;
        // print
    }

    void nextPrinter(/* parameters*/) {
        // print
    }
};

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

unsigned int countBits(const string &line) {
    size_t position = 0;
    unsigned int number = getUnsignedInteger(line, position);

    number = (number & 0x55555555) + ( ( number >> 1) & 0x55555555);
    number = (number & 0x33333333) + ( ( number >> 2) & 0x33333333);
    number = (number & 0x0f0f0f0f) + ( ( number >> 4) & 0x0f0f0f0f);
    number = (number & 0x00ff00ff) + ( ( number >> 8) & 0x00ff00ff);
    number = (number & 0x0000ffff) + ( ( number >> 16) & 0x0000ffff);

    return number;
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
        cout << countBits(inputLine) << endl;
    }

    return 0;
}
