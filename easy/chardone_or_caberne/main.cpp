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

bool print_vines(const string& line) {
    bool result = false;
    size_t letters_end = line.length();
    size_t letters_start = letters_end - 8;

    Printer<const char*> p;
    char *buffer = const_cast<char*>(line.c_str());

    while (buffer[letters_start] != '|') {
        ++letters_start;
    }

    letters_start += 2; // skip space delimiter


    size_t position = 0;
    while (buffer[position] != '|') {
        size_t  letters_i = letters_start;
        size_t  name_start = position;
        bool    print_name = false;

        while (buffer[position] != ' ') {
            for (size_t i = letters_i; i < letters_end; i++) {
                if (buffer[position] == buffer[i]) {
                    if (i != letters_i) {
                        char temp = buffer[i];
                        buffer[i] = buffer[letters_i];
                        buffer[letters_i] = temp;
                    }
                    ++letters_i;
                    break;
                }
            }
            if (letters_i == letters_end) {
                print_name = true;
                while (buffer[position] != ' ') {
                    ++position;
                }
                break;
            }

            ++position;
        }

        if (print_name) {
            result = true;
            buffer[position] = 0;
            p.print(&(buffer[name_start]));
        }
        ++position;
    }

    if (result) {
        cout << endl;
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
        if (!print_vines(inputLine)) {
            cout << "False" << endl;
        }
    }

    return 0;
}
