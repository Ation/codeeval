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

void eliminate(const string &line) {
    size_t position = 0;
    Printer p;

    unsigned int number;
    unsigned int index;

    getUnsignedInteger( line, position, number);
    getUnsignedInteger( line, position, index);

    vector<unsigned int> circle;
    circle.resize(number, 0);

    unsigned int eliminated = 0;
    unsigned int i = 0;

    while (eliminated != number) {
        // count
        unsigned int count = 0;
        while (true) {
            if (circle[i] == 0) {
                count++;
                if (count == index) {
                    break;
                }
            }
            i++;
            if (i == number) {
                i = 0;
            }
        }

        p.print(i);
        // eliminate
        circle[i] = 1;
        eliminated++;
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
        eliminate(inputLine);
    }

    return 0;
}
