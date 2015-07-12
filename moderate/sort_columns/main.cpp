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
    Printer(const unsigned int dimension) : m_printer(&Printer< value_type >::firstPrinter), m_dimension(dimension), m_count(0) {
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
        m_count++;
    }

    void nextPrinter(value_type value) {
        // print
        if (m_count == m_dimension) {
            cout << " | " << value;
            m_count = 1;
        } else {
            cout << ' ' << value;
            m_count++;
        }
    }

    unsigned int m_dimension;
    unsigned int m_count;
};

bool getInteger(const string &line, size_t &position, int &number) {
    int result = 0;
    bool negative = false;
    char temp;

    for (; position < line.length(); ++position) {
        temp = line[position];
        if (temp == '-') {
            negative = true;
            position++;
            break;
        }
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

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
            position++;
            break;
        }
    }

    if (negative) {
        result = -result;
    }

    number = result;

    return true;
}

void sort_columns(const string& line) {
    size_t position = 0;
    unsigned int dimension = 0;

    vector<int> numbers;
    int temp;

    while (getInteger(line, position, temp)) {
        if (line[position] == '|') {
            ++dimension;
        }

        numbers.push_back(temp);
    }

    ++dimension;
    Printer<int> printer(dimension);

    auto start = numbers.begin();
    auto end = start + dimension;

    while (start != numbers.end()) {
        sort(start, end);
        ++end;

        while( start != end) {
            printer.print(*start);
            ++start;
        }

        start = end;
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
        sort_columns(inputLine);
    }

    return 0;
}
