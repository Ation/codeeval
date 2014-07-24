#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(char *str);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(char *str) {
        (this->*m_printer)(str);
    }
private:
    printerFunction m_printer;

    void firstPrinter(char *str) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << str ;
    }

    void nextPrinter(char *str) {
        cout << ',' << str ;
    }
};

typedef char (*next_symbol_function)(int &state, bool &overflow);

char next_0(int &state, bool &overflow) {
    state = 0;
    overflow = true;
    return '0';
}

char next_1(int &state, bool &overflow) {
    state = 0;
    overflow = true;
    return '1';
}

char next_2(int &state, bool &overflow) {
    static const char symbols[] = "abc";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_3(int &state, bool &overflow) {
    static const char symbols[] = "def";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_4(int &state, bool &overflow) {
    static const char symbols[] = "ghi";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_5(int &state, bool &overflow) {
    static const char symbols[] = "jkl";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_6(int &state, bool &overflow) {
    static const char symbols[] = "mno";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_7(int &state, bool &overflow) {
    static const char symbols[] = "pqrs";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_8(int &state, bool &overflow) {
    static const char symbols[] = "tuv";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

char next_9(int &state, bool &overflow) {
    static const char symbols[] = "wxyz";
    static const int size = (sizeof(symbols)/sizeof(symbols[0])) - 1;

    state++;
    if (state == size) {
        overflow = true;
        state = 0;
    }
    return symbols[state];
}

static next_symbol_function next_symbol_table[] = {
    next_0,
    next_1,
    next_2,
    next_3,
    next_4,
    next_5,
    next_6,
    next_7,
    next_8,
    next_9
};

void printPhoneWords(const string &line) {
    // read number
    // start to iterate
    char str[8];
    int  states[7];
    next_symbol_function next_symbol[7];
    bool overflow;
    Printer printer;
    int i;

    for (i=0; i < 7; i++) {
        states[i] = -1;
        next_symbol[i] = next_symbol_table[line[i] - '0'];
        str[i] = next_symbol[i](states[i], overflow);
    }

    str[7] = 0;

    printer.print(str);
    while (true) {
        i = 6;
        for (i = 6; i >= 0; i--) {
            overflow = false;
            str[i] = next_symbol[i](states[i], overflow);
            if (!overflow) {
                break;
            }
        }

        if (overflow) {
            break;
        }
        printer.print(str);
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
        printPhoneWords(inputLine);
    }

    return 0;
}
