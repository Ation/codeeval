#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(unsigned int);

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
        cout << value;
    }

    void nextPrinter(unsigned int value) {
        cout << ' ' << value;
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

void multiplyLists(const string &line) {
    Printer     printer;

    size_t  left_position = 0;
    size_t  right_position = 0;

    unsigned int left;
    unsigned int right;

    while (line[right_position]  != '|') {
        right_position++;
    }
    right_position += 2;

    while (right_position < line.length()) {
        left = getUnsignedInteger(line, left_position);
        right = getUnsignedInteger(line, right_position);

        printer.print(left * right);
    }

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
        multiplyLists(inputLine);
    }

    return 0;
}
