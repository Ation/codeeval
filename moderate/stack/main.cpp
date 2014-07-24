#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(const char *str);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(const char *str) {
        (this->*m_printer)(str);
    }
private:
    printerFunction m_printer;

    void firstPrinter(const char *str) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << str;
    }

    void nextPrinter(const char *str) {
        // print
        cout << ' ' << str;
    }
};

void back(const char *str, int &start, int &end) {
    while ((end > 0) && (str[end] == ' ')) {
        end --;
    }

    start = end;
    while ((start > 0) && (str[start] != ' ')) {
        start --;
    }

    if ((str[start] == ' ') && (start != 0)) {
        start++;
    }
}

void stackPrintAlternate(const string &line) {
    int end;
    int start;
    char *data = const_cast<char*>(line.c_str());
    Printer p;

    end = line.length() - 1;

    back(data, start, end);
    p.print(&( data[start] ));

    while (true) {
        end = start - 1;
        back(data, start, end);
        if (start <= 0) {
            break;
        }

        end = start - 1;
        back(data, start, end);
        data[end + 1] = 0;

        if (end < 0) {
            break;
        }
        p.print(&( data[start] ));
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
        stackPrintAlternate(inputLine);
    }

    return 0;
}
