#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(int value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(int value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(int value) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << value;
    }

    void nextPrinter(int value) {
        // print
        cout << ',' << value;
    }
};

bool getInteger(const string &line, size_t &position, int &number) {
    int result = 0;
    bool negative = false;

    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp == '-') {
            negative = true;
            position++;
            break;
        }
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
            position++;
            break;
        }
    }

    if (negative) {
        result = -result;
    }
    number = result;
    return true;
}

class Hole {
public:
    Hole(int dx, int dy) : m_dx(dx), m_dy(dy) {

    }

    int getDx() const { return m_dx; }
    int getDy() const { return m_dy; }

private:
    int m_dx;
    int m_dy;
};

class Brick {
public:
    Brick() {

    }

    bool setSize(const string &line, size_t &position) {
        int x1;
        int x2;
        int y1;
        int y2;
        int z1;
        int z2;

        if (!getInteger(line, position, m_index)) {
            return false;
        }

        if (!getInteger(line, position, x1)) {
            return false;
        }

        if (!getInteger(line, position, y1)) {
            return false;
        }

        if (!getInteger(line, position, z1)) {
            return false;
        }

        if (!getInteger(line, position, x2)) {
            return false;
        }

        if (!getInteger(line, position, y2)) {
            return false;
        }

        if (!getInteger(line, position, z2)) {
            return false;
        }

        m_dx = x1 - x2;
        m_dy = y1 - y2;
        m_dz = z1 - z2;

        if (m_dx < 0) {
            m_dx = -m_dx;
        }
        if (m_dy < 0) {
            m_dy = -m_dy;
        }
        if (m_dz < 0) {
            m_dz = -m_dz;
        }

        return true;
    }

    bool couldPassThrough(const Hole& hole) {
        return     couldPass(m_dx, m_dy, hole.getDx(), hole.getDy())
                || couldPass(m_dx, m_dz, hole.getDx(), hole.getDy())
                || couldPass(m_dy, m_dz, hole.getDx(), hole.getDy());
    }

    int getIndex() const { return m_index; }
private:
    bool couldPass(int brick_1, int brick_2, int hole_1, int hole_2) {
        return ( ( (brick_1 <= hole_1) && (brick_2 <= hole_2) )
              || ( (brick_2 <= hole_1) && (brick_1 <= hole_2) ));
    }

    int m_dx;
    int m_dy;
    int m_dz;

    int m_index;
};

Hole readHole(const string &line, size_t &position) {
    int x1;
    int x2;
    int y1;
    int y2;

    getInteger(line, position, x1);
    getInteger(line, position, y1);

    getInteger(line, position, x2);
    getInteger(line, position, y2);

    x1 = x1 - x2;
    if (x1 < 0) {
        x1 = -x1;
    }

    y1 = y1-y2;
    if (y1 < 0) {
        y1 = -y1;
    }

    return Hole(x1,y1);
}

void processBricks(const string &line) {
    size_t position = 0;
    Printer p;
    bool    printed = false;

    Hole hole = readHole(line, position);
    Brick   brick;

    while (brick.setSize(line, position)) {
        if (brick.couldPassThrough(hole)) {
            p.print(brick.getIndex());
            printed = true;
        }
    }

    if (!printed) {
        cout << '-' << endl;
    } else {
        cout << endl;
    }
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
        processBricks(inputLine);
    }

    return 0;
}
