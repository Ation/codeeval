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
        cout << ',' << value;
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
            break;
        }
    }

    number = result;
    return true;
}

void printReversed(const string &line) {
    size_t position = 0;
    Printer p;
    unsigned int number;

    static vector<int> values;

    values.clear();

    while (line[position] != ';') {
        getUnsignedInteger(line, position, number);
        values.push_back(number);
    }

    getUnsignedInteger(line, position, number);

    if (number > values.size() ) {
        number = values.size();
    }

    int start = number - 1;
    while (start < values.size() ) {
        for (int i = start; i > start - (int)number; --i) {
            p.print(values[i]);
        }
        start += number;
    }

    for (int i = start - number + 1; i < values.size(); i++) {
        p.print(values[i]);
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
        printReversed(inputLine);
    }

    return 0;
}
