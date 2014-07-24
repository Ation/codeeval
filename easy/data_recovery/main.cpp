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
        cout << ' ' << str ;
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

void printRecovered(const string &line) {
    // read words
    vector<size_t> wordStart;
    vector<int> index;
    Printer     p;

    unsigned int nextIndex;

    bool readWords = true;

    char *str = const_cast<char*>(line.c_str());
    size_t position = 0;

    while (readWords) {
        wordStart.push_back(position);
        while(str[position] != ' ' && str[position] != ';') {
            position++;
        }
        if (str[position] == ';') {
            readWords = false;
        }
        str[position] = 0;
        position++;
    }

    // read real index array
    index.resize(wordStart.size(), -1);
    int i=0;
    while (getUnsignedInteger(line, position, nextIndex)) {
        index[nextIndex - 1] = i;
        i++;
    }

    for (int j=0; j < index.size(); j++) {
        if (index[j] == -1) {
            p.print( &( str[ wordStart[i] ] ) );
            i++;
        } else {
            p.print( &( str[ wordStart[ index[j] ] ] ) );
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
        printRecovered(inputLine);
    }

    return 0;
}
