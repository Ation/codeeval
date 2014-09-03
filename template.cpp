#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

template< class _T >
class Printer {
private:
    typedef _T value_type;
    typedef void (Printer< value_type >::*printerFunction)(value_type value);

public:
    Printer() : m_printer(&Printer< value_type >::firstPrinter) {
    }

    void print(value_type value) {
        (this->*m_printer)( value );
    }
private:
    printerFunction m_printer;

    void firstPrinter(value_type value) {
        m_printer = &Printer< value_type >::nextPrinter;
        // print
        cout << value ;
    }

    void nextPrinter(value_type value) {
        // print
        cout << ' ' << value;
    }
};

bool getDouble(const string &line, size_t &position, double &number) {
    bool negative = false;
    double result = 0;
    char symbol;
    // find start
    for (; position < line.length(); position++ ) {
        symbol = line[position];
        if (symbol == '-') {
            negative = true;
            position++;
            break;
        }
        if (symbol >= '0' && symbol <= '9') {
            break;
        }
    }

    if (position == line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        symbol = line[position];
        if (symbol == '.') {
            int devider = 10;

            // after dot
            position++;
            for (; position < line.length(); position++) {
                symbol = line[position];
                if (symbol >= '0' && symbol <= '9') {
                    result = result + ((double)(symbol - '0')) / devider;
                    devider *= 10;
                } else {
                    break;
                }
            }
            break;
        } else if (symbol >= '0' && symbol <= '9') {
            result = result * 10 + (symbol - '0');
        } else {
            break;
        }
    }

    if (negative) {
        result = -result;
    }

    number = result;
    return true;
}

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
