#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(int index, const unsigned long long int &count);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(int index, const unsigned long long int &count) {
        (this->*m_printer)(index, count);
    }
private:
    printerFunction m_printer;

    void firstPrinter(int index, const unsigned long long int &count) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << index << ": " << count;
    }

    void nextPrinter(int index, const unsigned long long int &count) {
        // print
        cout << ", " << index << ": " << count;
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

bool getUnsignedLongLongInteger(const string &line, size_t &position, unsigned long long int &number) {
    unsigned long long int result = 0;
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

void printStat(const string &line) {
    unsigned int number;
    unsigned long long int count;
    Printer     p;

    vector<unsigned long long int> stat;

    stat.resize(10, 0);

    size_t position = 0;

    getUnsignedInteger(line, position, number);
    getUnsignedLongLongInteger(line, position, count);

    switch(number) {
    case 2:
        {
            int left = count & 3;
            stat[8] = stat[4] = stat[6] = stat[2] = count >> 2;
            switch(left) {
            case 3:
                stat[8]++;
            case 2:
                stat[4]++;
            case 1:
                stat[2]++;
                break;
            }
        }
        break;
    case 3:
        {
            int left = count & 3;
            stat[7] = stat[9] = stat[3] = stat[1] = count >> 2;
            switch (left) {
            case 3:
                stat[7]++;
            case 2:
                stat[9]++;
            case 1:
                stat[3]++;
                break;
            default:
                break;
            }
        }
        break;
    case 4:
        stat[4] = stat[6] = count >> 1;
        stat[4] += count & 1;
        break;
    case 5:
        stat[5] = count;
        break;
    case 6:
        stat[6] = count;
        break;
    case 7:
        {
            int left = count & 3;
            stat[7] = stat[9] = stat[3] = stat[1] = count >> 2;
            switch (left) {
            case 3:
                stat[3]++;
            case 2:
                stat[9]++;
            case 1:
                stat[7]++;
                break;
            default:
                break;
            }
        }
        break;
    case 8:
        {
            int left = count & 3;
            stat[8] = stat[4] = stat[2] = stat[6] = count >> 2;
            switch(left) {
            case 3:
                stat[2]++;
            case 2:
                stat[4]++;
            case 1:
                stat[8]++;
                break;
            }
        }
        break;
    case 9:
        stat[9] = stat[1] = count >> 1;
        stat[9] += count & 1;
        break;
    }

    for (unsigned int i=0; i < stat.size(); i++) {
        p.print(i, stat[i]);
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
        printStat(inputLine);
    }

    return 0;
}
