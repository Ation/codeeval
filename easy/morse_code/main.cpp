#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;


template<unsigned long N>
struct bin {
    enum { value = (N%10)+2*bin<N/10>::value };
} ;

template<>
struct bin<0> {
    enum { value = 0 };
};

class MorseTable {
public:
    MorseTable() {
        initTable();
    }

    bool getSymbol(const string &line, size_t &position, char &symbol) {
        unsigned int code = 1;

        if (position >= line.length()) {
            return false;
        }

        if (line[position] == ' ') {
            position++;
            symbol = ' ';
            return true;
        }

        for (; position < line.length() && line[position] != ' '; position++) {
            code <<= 1;
            if (line[position] == '-') {
                code |= 1;
            }
        }
        position++;

        symbol = m_table[code];

        return true;
    }
private:
    map<unsigned int, char> m_table;

    void initTable() {
        m_table.insert( pair<unsigned int, char>(bin<101>::value, 'A') );
        m_table.insert( pair<unsigned int, char>(bin<11000>::value, 'B') );
        m_table.insert( pair<unsigned int, char>(bin<11010>::value, 'C') );
        m_table.insert( pair<unsigned int, char>(bin<1100>::value, 'D') );
        m_table.insert( pair<unsigned int, char>(bin<10>::value, 'E') );
        m_table.insert( pair<unsigned int, char>(bin<10010>::value, 'F') );
        m_table.insert( pair<unsigned int, char>(bin<1110>::value, 'G') );
        m_table.insert( pair<unsigned int, char>(bin<10000>::value, 'H') );
        m_table.insert( pair<unsigned int, char>(bin<100>::value, 'I') );
        m_table.insert( pair<unsigned int, char>(bin<10111>::value, 'J') );
        m_table.insert( pair<unsigned int, char>(bin<1101>::value, 'K') );
        m_table.insert( pair<unsigned int, char>(bin<10100>::value, 'L') );
        m_table.insert( pair<unsigned int, char>(bin<111>::value, 'M') );
        m_table.insert( pair<unsigned int, char>(bin<110>::value, 'N') );
        m_table.insert( pair<unsigned int, char>(bin<1111>::value, 'O') );
        m_table.insert( pair<unsigned int, char>(bin<10110>::value, 'P') );
        m_table.insert( pair<unsigned int, char>(bin<11101>::value, 'Q') );
        m_table.insert( pair<unsigned int, char>(bin<1010>::value, 'R') );
        m_table.insert( pair<unsigned int, char>(bin<1000>::value, 'S') );
        m_table.insert( pair<unsigned int, char>(bin<11>::value, 'T') );
        m_table.insert( pair<unsigned int, char>(bin<1001>::value, 'U') );
        m_table.insert( pair<unsigned int, char>(bin<10001>::value, 'V') );
        m_table.insert( pair<unsigned int, char>(bin<1011>::value, 'W') );
        m_table.insert( pair<unsigned int, char>(bin<11001>::value, 'X') );
        m_table.insert( pair<unsigned int, char>(bin<11011>::value, 'Y') );
        m_table.insert( pair<unsigned int, char>(bin<11100>::value, 'Z') );
        m_table.insert( pair<unsigned int, char>(bin<101111>::value, '1') );
        m_table.insert( pair<unsigned int, char>(bin<100111>::value, '2') );
        m_table.insert( pair<unsigned int, char>(bin<100011>::value, '3') );
        m_table.insert( pair<unsigned int, char>(bin<100001>::value, '4') );
        m_table.insert( pair<unsigned int, char>(bin<100000>::value, '5') );
        m_table.insert( pair<unsigned int, char>(bin<110000>::value, '6') );
        m_table.insert( pair<unsigned int, char>(bin<111000>::value, '7') );
        m_table.insert( pair<unsigned int, char>(bin<111100>::value, '8') );
        m_table.insert( pair<unsigned int, char>(bin<111110>::value, '9') );
        m_table.insert( pair<unsigned int, char>(bin<111111>::value, '0') );
    }
};

void decodeMorse(const string &line, MorseTable &table) {
    char symbol;
    size_t position = 0;

    while (table.getSymbol(line, position, symbol)) {
        cout << symbol;
    }

    cout << endl;
}

int main(int argc, char *argv[]) {
    MorseTable table;

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        decodeMorse(inputLine, table);
    }

    return 0;
}
