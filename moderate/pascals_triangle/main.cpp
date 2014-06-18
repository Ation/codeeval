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

void printPascal(const string &line) {
    unsigned int depth;
    size_t position = 0;

    Printer p;

    getUnsignedInteger(line, position, depth);

    vector<unsigned int> values;
    values.reserve((depth + 1) / 2);

    values.push_back(1);

    for (unsigned int i = 1; i <= depth; i++) {
        if (i < 3) {
            for (unsigned int j=0; j < i; j++) {
                p.print(1);
            }
        } else {
            unsigned int temp = values[0];
            unsigned int next;

            for (unsigned int j = 1; j < values.size(); j++) {
                next = values[j];
                values[j] = temp + next;
                temp = next;
            }

            if ((i & 1) == 1) {
                values.push_back(temp * 2);

                for (unsigned int j=0; j < values.size(); j++) {
                    p.print(values[j]);
                }

                for (int j = values.size() - 2; j >= 0; --j) {
                    p.print(values[j]);
                }
            } else {
                for (unsigned int j=0; j < values.size(); j++) {
                    p.print(values[j]);
                }

                for (int j = values.size() - 1; j >= 0; --j) {
                    p.print(values[j]);
                }
            }
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
        printPascal(inputLine);
    }

    return 0;
}
