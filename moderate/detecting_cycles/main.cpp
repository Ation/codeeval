#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(unsigned int value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(unsigned int value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(unsigned int value) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << value;
    }

    void nextPrinter(unsigned int value) {
        // print
        cout << ' ' << value;
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

bool endsWithLoop(const vector<unsigned int> &sequence, unsigned int length) {
    if ((length << 1) > sequence.size()) {
        return false;
    }

    for (unsigned int i = sequence.size() - length; i < sequence.size(); i++) {
        if (sequence[i] != sequence[i - length]) {
            return false;
        }
    }

    return true;
}

bool loopRepeated(const vector<unsigned int> &sequence, unsigned int big_loop, unsigned int small_loop) {
    unsigned int repeat_count = big_loop / small_loop;
    if (small_loop * repeat_count != big_loop) {
        return false;
    }

    for (unsigned int i=sequence.size() - small_loop; i < sequence.size(); i++) {
        for (unsigned int j = i - (small_loop * (repeat_count - 1)); j < i; j += small_loop) {
            if (sequence[i] != sequence[j]) {
                return false;
            }
        }
    }

    return true;
}

void printCycle(const string &line) {
    size_t position = 0;
    static vector<unsigned int> sequence;
    Printer p;

    sequence.clear();

    unsigned int number;

    while (getUnsignedInteger(line, position, number)) {
        sequence.push_back(number);
    }

    unsigned int loop_length = 1;
    unsigned int found_length = 0;
    bool loop_detected = false;

    while ((loop_length << 1) <= sequence.size()) {
        if (endsWithLoop(sequence, loop_length)) {
            if (!loop_detected || !loopRepeated(sequence, loop_length, found_length)) {
                found_length = loop_length;
                loop_detected = true;
            }
        }
        loop_length++;
    }

    if ( !loop_detected) {
        found_length = sequence.size();
    }

    for (int i = sequence.size() - found_length; i < sequence.size(); ++i) {
        p.print(sequence[i]);
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
        printCycle(inputLine);
    }

    return 0;
}
