#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <algorithm>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(double number);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(double number) {
        (this->*m_printer)(number);
    }
private:
    printerFunction m_printer;

    void firstPrinter(double number) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << number;
    }

    void nextPrinter(double number) {
        // print
        cout << ' ' << number;
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

void sortLine(const string &line) {
    double number;
    size_t position = 0;
    vector<double> numbers;
    Printer p;

    while (getDouble(line, position, number)) {
        numbers.push_back(number);
    }

    sort(numbers.begin(), numbers.end());
    for(auto&& n : numbers) {
        p.print(n);
    }

    cout << endl;
}

int main(int argc, char *argv[]) {
    cout << fixed << setprecision(3);

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        sortLine(inputLine);
    }

    return 0;
}
