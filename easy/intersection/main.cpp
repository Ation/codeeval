#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

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

class Printer {
private:
    typedef void (Printer::*printerFunction)(int value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(int value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(int value) {
        m_printer = &Printer::nextPrinter;
        cout << value;
    }

    void nextPrinter(int value) {
        cout << ',' << value;
    }
};

void printIntersection(const string &line) {
    size_t first_position;
    size_t second_position;

    size_t delimiter_position;

    Printer printer;

    for (delimiter_position=0; delimiter_position < line.length(); delimiter_position++) {
        if (line[delimiter_position] == ';' ) {
            break;
        }
    }

    first_position = 0;
    second_position = delimiter_position + 1;

    unsigned int first = getUnsignedInteger(line, first_position);
    unsigned int second = getUnsignedInteger(line, second_position);

    while (true) {
        if (first == second) {
            printer.print(first);

            if (first_position >= delimiter_position) {
                break;
            }
            first = getUnsignedInteger(line, first_position);

            if (second_position >= line.length()) {
                break;
            }
            second = getUnsignedInteger(line, second_position);
        } else if ( first < second) {
            if (first_position >= delimiter_position) {
                break;
            }
            first = getUnsignedInteger(line, first_position);
        } else {
            if (second_position >= line.length()) {
                break;
            }
            second = getUnsignedInteger(line, second_position);
        }
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
        printIntersection(inputLine);
    }

    return 0;
}
