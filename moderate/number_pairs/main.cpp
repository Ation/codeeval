#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int getIntegerItem(const string &line, size_t &position, bool &last) {
    last = false;

    int result = 0;

    for (; position < line.length(); position++) {
        if (line[position] == ',') {
            position++;
            break;
        } else if (line[position] == ';') {
            position++;
            last = true;
            break;
        } else {
            result = result * 10 + (line[position] - '0');
        }
    }

    return result;
}

class Printer {
private:
    typedef void (Printer::*printerFunction)(int, int);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }
    
    void print(int one, int two) {
        (this->*m_printer)(one, two);
    }
private:
    printerFunction m_printer;
    
    void firstPrinter(int one, int two) {
        m_printer = &Printer::nextPrinter;
        cout << one << ',' << two;
    }
    
    void nextPrinter(int one, int two) {
        cout << ';' << one << ',' << two;
    }
};

void printPairsNumber(const string& line, vector<int> &container) {
    container.clear();

    bool    last = false;
    bool    found = false;

    size_t  position = 0;
    while (!last) {
        container.push_back(getIntegerItem(line, position, last) );
    }

    int target_sum = getIntegerItem(line, position, last);
    int i=0;
    int j = container.size() - 1;

    if (target_sum > 2 * container[j]) {
        cout << "NULL" << endl;
        return;
    }

    int sum;
    Printer p;

    while ( i < j) {
        sum = container[i] + container[j];

        if (sum == target_sum) {
            found = true;
            p.print(container[i], container[j]);
            i++;
            j--;
        } else if (sum > target_sum) {
            j--;
        } else {
            i++;
        }
    }


    if (!found) {
        cout << "NULL" << endl;
        return;
    } else {
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    vector<int> sharedContainer;

    sharedContainer.reserve(35);

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        printPairsNumber(inputLine, sharedContainer);
    }

    return 0;
}
