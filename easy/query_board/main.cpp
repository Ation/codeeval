#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

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

class Board {
public:
    Board() {
        initBoard();
    }

    void setRow(int row, unsigned int value) {
        for (int i=0; i < 256; i++) {
            m_board[row][i] = value;
        }
    }

    void setColumn(int column, unsigned int value) {
        for (int i=0; i < 256; i++) {
            m_board[i][column] = value;
        }
    }

    int getRow(unsigned int row) {
        int result = 0;

        for (int i=0; i < 256; i++) {
            result += m_board[row][i];
        }

        return result;
    }

    int getColumn(unsigned int column) {
        int result = 0;

        for (int i=0; i < 256; i++) {
            result += m_board[i][column];
        }

        return result;
    }

private:
    void initBoard() {
        for (int i=0; i < 256; i++) {
            for (int j=0; j < 256; j++) {
                m_board[i][j] = 0;
            }
        }
    }

    int m_board[256][256];
};

void executeQuery(const string &line, Board *board) {
    size_t position;
    if (line[0] == 'S') {
        unsigned int index;
        unsigned int value;
        position = 6;

        getUnsignedInteger(line, position, index);
        getUnsignedInteger(line, position, value);

        if (line[3] == 'C') {
            board->setColumn(index, value);
        } else {
            board->setRow(index, value);
        }
    } else {
        unsigned int index;
        position = 8;
        getUnsignedInteger(line, position, index);

        if (line[5] == 'C') {
            cout << board->getColumn(index) << endl;
        } else {
            cout << board->getRow(index) << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    Board *board = new Board();

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        executeQuery(inputLine, board);
    }

    return 0;
}
