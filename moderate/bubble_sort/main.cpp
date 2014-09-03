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

void sort_partially( const string &line ) {
    vector< unsigned int > items;
    size_t  position = 0;
    unsigned int max_operations;
    unsigned int temp;

    getUnsignedInteger( line, position, max_operations );
    temp = max_operations;

    while ( getUnsignedInteger( line, position, max_operations ) ) {
        items.emplace_back( temp );
        temp = max_operations;
    }

    bool changed;
    unsigned int operations_count = 0;


    do {
        changed = false;

        for (size_t i = 1; i < items.size(); i++) {
            if ( items[i] < items[ i - 1 ]) {
                // swap
                temp = items[i];
                items[i] = items[i-1];
                items[i-1] = temp;

                changed = true;
            }
        }

        operations_count++;
    } while ( ( operations_count < max_operations ) && changed );

    Printer<unsigned int> p;

    for(auto&& i : items) {
        p.print(i);
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
        sort_partially( inputLine );
    }

    return 0;
}
