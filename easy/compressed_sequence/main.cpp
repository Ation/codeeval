#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(unsigned int value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(unsigned int value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(unsigned int value) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << value;
    }

    void nextPrinter(unsigned int value) {
        // print
        cout << ' ' << value;
    }
};

bool getUnsignedInteger(const string &line, size_t &position, unsigned int &number) {
    unsigned int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

    if (position >= line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

void compressSequence(const string &line) {
    size_t position = 0;
    unsigned int count = 1;
    unsigned int number;
    unsigned int current;

    Printer     printer;

    getUnsignedInteger(line, position, number);

    while (getUnsignedInteger(line, position, current)) {
        if (current == number) {
            count ++;
        } else {
            printer.print(count);
            printer.print(number);
            count = 1;
            number = current;
        }
    }

    printer.print(count);
    printer.print(number);

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
        compressSequence(inputLine);
    }

    return 0;
}
