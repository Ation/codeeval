#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

class Printer {
private:
    using value_type = unsigned int;
    typedef void (Printer::*printerFunction)(value_type value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(value_type value) {
        (this->*m_printer)( value );
    }
private:
    printerFunction m_printer;

    void firstPrinter(value_type value) {
        m_printer = &Printer::nextPrinter;
        // print
        if (value < 10) {
            cout << '0' ;
        }
        cout << value ;
    }

    void nextPrinter(value_type value) {
        // print
        cout << ':';
        if (value < 10) {
            cout << '0' ;
        }
        cout << value ;
    }
};

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

typedef struct __my_time {
    int hh;
    int mm;
    int ss;
}my_time;

void readTime(const string &line, size_t &position, my_time &mt) {
    mt.hh = getUnsignedInteger(line, position);
    mt.mm = getUnsignedInteger(line, position);
    mt.ss = getUnsignedInteger(line, position);
}

int compareTime( const my_time& mt1, const my_time& mt2 ) {
    if (mt1.hh > mt2.hh) {
        return 1;
    }
    if (mt1.hh < mt2.hh) {
        return -1;
    }

    if (mt1.mm > mt2.mm) {
        return 1;
    }
    if (mt1.mm < mt2.mm) {
        return -1;
    }

    if (mt1.ss > mt2.ss) {
        return 1;
    }
    if (mt1.ss < mt2.ss) {
        return -1;
    }

    return 0;
}

void subtractTime(const my_time& from, const my_time& what, my_time &result) {
    result.hh = from.hh - what.hh;
    result.mm = from.mm - what.mm;
    result.ss = from.ss - what.ss;

    if (result.ss < 0) {
        result.ss += 60;
        result.mm--;
    }
    if (result.mm < 0) {
        result.mm += 60;
        result.hh--;
    }
}

void getDiff( const my_time& mt1, const my_time& mt2, my_time &diff) {
    int compare_result = compareTime(mt1, mt2);

    if (compare_result == 0) {
        memset(&diff, 0, sizeof( diff ));
    } else if (compare_result > 0) {
        subtractTime(mt1, mt2, diff);
    } else {
        subtractTime(mt2, mt1, diff);
    }
}

void printDeltaTime( const string &line) {
    size_t position = 0;

    my_time mt1;
    my_time mt2;

    my_time diff;

    readTime(line, position, mt1);
    readTime(line, position, mt2);

    getDiff(mt1, mt2, diff);

    Printer p;
    p.print(diff.hh);
    p.print(diff.mm);
    p.print(diff.ss);
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
        printDeltaTime(inputLine);
    }

    return 0;
}
