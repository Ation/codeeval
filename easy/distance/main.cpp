#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

int getInteger(const string &line, size_t &position) {
    int result = 0;
    bool negative = false;
    char temp;

    do {
        if (position == line.length()) {
            return 0;
        }

        if ( (line[position] == '-') || ((line[position] >= '0' && line[position] <= '9')) ) {
            break;
        }
        position++;
    } while (true);

    if (line[position] == '-') {
        negative = true;
        position++;
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

    return result;
}

class Point {
public:
    Point(int x, int y) : m_x(x), m_y(y) {
    }

    double distanceTo(const Point& other) {
        double result = 0;

        int dx = other.m_x - m_x;
        int dy = other.m_y - m_y;

        result = sqrt(dx * dx + dy * dy);

        return result;
    }

    static Point readPoint(const string &line, size_t &position) {
        int x;
        int y;

        // find start
        for (; ( position < line.length() ) && ( line[position] != '(' ) ; position++) {
        }

        x = getInteger(line, position);
        y = getInteger(line, position);

        return Point(x, y);
    }
private:
    int m_x;
    int m_y;
};

void printDistance(const string &line) {
    size_t position = 0;
    Point p1 = Point::readPoint(line, position);
    Point p2 = Point::readPoint(line, position);

    double distance = p1.distanceTo(p2);

    cout << distance << endl;
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
        printDistance(inputLine);
    }

    return 0;
}
