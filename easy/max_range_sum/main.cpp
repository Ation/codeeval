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

int getInteger(const string &line, size_t &position) {
    int result = 0;
    bool negative = false;
    char temp;

    while (position < line.length() ) {
        temp = line[position];
        if (temp == '-') {
            negative = true;
            position++;
            break;
        }

        if (temp >= '0' && temp <= '9') {
            break;
        }
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

int max_sum( const string& line) {
    size_t position = 0;

    int count = getInteger( line, position);
    int sum = 0;
    int max = 0;
    int i = 0;

    vector<int> numbers;

    while ( position < line.length() ) {
        numbers.push_back( getInteger(line, position) );
    }

    for ( i = 0; i < count; i++) {
        sum += numbers[i];
    }

    max = sum;

    for (; i < numbers.size(); i++) {
        sum += numbers[i];
        sum -= numbers[i - count];

        if (sum > max) {
            max = sum;
        }
    }

    return (max > 0 ? max : 0);
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
        cout << max_sum( inputLine) << endl;
    }

    return 0;
}
