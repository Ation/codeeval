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
    int result = 0;
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

int getInteger(const string &line, size_t &position) {
    int result = 0;
    bool negative = false;
    char temp;

    if (line[position] == '-') {
        negative = true;
        position++;
    }

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
        result = -result;
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

    }

    return 0;
}
