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
    unsigned int _counter = 0;

    void firstPrinter(value_type value) {
        m_printer = &Printer< value_type >::nextPrinter;
        // print
        cout << value ;
    }

    void nextPrinter(value_type value) {
        // print
        _counter++;
        cout << ' ';
        for (unsigned int i=0; i < _counter; i++) {
            cout << '*';
        }
        cout <<  value;
    }

};

void print_longest_word(const string& line) {
    unsigned int longest = 0;
    unsigned int longest_start = 0;
    unsigned int longets_end = 0;

    unsigned int start = 0;
    unsigned int end = 0;

    Printer<char> p;

    while(end <= line.length() ) {
        if (end == line.length() || line[end] == ' ') {
            if (end - start > longest) {
                longest_start = start;
                longets_end = end;
                longest = end - start;
            }
            start = end + 1;
            end = start + 1;
        } else {
            ++end;
        }
    }

    for (; longest_start != longets_end; longest_start++) {
        p.print(line[longest_start]);
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
        print_longest_word(inputLine);
    }

    return 0;
}
