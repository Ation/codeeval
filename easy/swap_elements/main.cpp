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
        if (temp == ':') {
            position++;
            return false;
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

void swapElements(const string &line) {
    vector<unsigned int> elements;
    size_t  position = 0;
    unsigned int index1;
    unsigned int index2;
    unsigned int temp;

    Printer     elementsPrinter;

    elements.reserve(line.length() / 2);

    // read elements
    while (getUnsignedInteger(line, position, index1) ) {
        elements.push_back(index1);
    }

    while (true) {
        if (!getUnsignedInteger(line, position, index1)) {
            break;
        }
        if (!getUnsignedInteger(line, position, index2)) {
            break;
        }

        temp = elements[index1];
        elements[index1] = elements[index2];
        elements[index2] = temp;
    }

    for(auto&& value : elements) {
        elementsPrinter.print(value);
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
        swapElements(inputLine);
    }

    return 0;
}
