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
    typedef void (Printer::*printerFunction)(const string &str);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(const string &str) {
        (this->*m_printer)(str);
    }
private:
    printerFunction m_printer;

    void firstPrinter(const string &str) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << str;
    }

    void nextPrinter(const string &str) {
        // print
        cout << ',' << str;
    }
};

bool increment(string &line) {
    unsigned int start = line.length() - 1;
    unsigned int i;

    for (i = start; i > 0; --i) {
        if (line[i] > line[i - 1]) {
            while (line[start] <= line[i-1]) {
                --start;
            }

            char temp = line[start];
            line[start] = line[i-1];
            line[i-1] = temp;

            sort(line.begin() + i, line.end());
            break;
        }
    }

    return i != 0;
}

void permute(string &line) {
    Printer p;

    sort(line.begin(), line.end());
    p.print(line);

    while ( increment(line) ) {
        p.print( line );
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
        permute( inputLine );
    }

    return 0;
}
