#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(const string &line);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(const string &line) {
        (this->*m_printer)(line);
    }

    void reset() {
        m_printer = &Printer::firstPrinter;
    }
private:
    printerFunction m_printer;

    void firstPrinter(const string &line) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << line;
    }

    void nextPrinter(const string &line) {
        // print
        cout << ',' << line;
    }
};

void separateContent(const string &line) {
    size_t  start = 0;
    size_t  length = 0;
    size_t  end;

    list<string>    words;
    list<string>    numbers;

    Printer         linePrinter;

    while (start < line.length()) {
        end = start + 1;
        while (end < line.length()) {
            if (line[end] == ',') {
                break;
            }

            end++;
        }

        length = end - start;

        if (line[start] >= '0' && line[start] <= '9') {
            numbers.emplace_back(line, start, length);
        } else {
            words.emplace_back(line, start, length);
        }
        start = end + 1;
    }

    if (!words.empty()) {
        for(auto&& word : words) {
            linePrinter.print(word);
        }

        if (!numbers.empty()) {
            cout << '|';
            linePrinter.reset();
        }
    }

    if (!numbers.empty()) {
        for(auto&& number : numbers) {
            linePrinter.print(number);
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
        separateContent(inputLine);
    }

    return 0;
}
