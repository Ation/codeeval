#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

typedef struct __point {
    int x;
    int y;
}Point;

int getInteger(const string& line, size_t &position) {
    bool negative = false;

    int result = 0;
    bool end = false;

    while (position < line.length() && !end) {
        if (line[position] == '-') {
            negative = true;            
        } else if (line[position] == ',') {
            end = true;
        } else {
            result = result * 10 + (line[position] - '0');
        }

        position++;
    }

    if (negative) {
        result = -result;
    }

    return result;
}

Point getPoint(const string &line, size_t &startPosition) {
    int x = getInteger(line, startPosition);
    int y = getInteger(line, startPosition);

    return Point { .x = x, .y = y};
}

bool isBetween(int low, int high, int target) {
    return (target >= low) && (target <= high);
}

bool checkCubeOverlap(const Point &ul1, const Point &br1, const Point &ul2, const Point &br2) {
    if (isBetween(ul1.x, br1.x, ul2.x) || isBetween(ul1.x, br1.x, br2.x)) {
        return isBetween(br1.y, ul1.y, ul2.y) || isBetween(br1.y, ul1.y, br2.y);
    }
    return false;
}

bool checkCubeOverlap(const string &testLine) {
    size_t position = 0;
    auto ul1 = getPoint(testLine, position);
    auto br1 = getPoint(testLine, position);
    auto ul2 = getPoint(testLine, position);
    auto br2 = getPoint(testLine, position);

    return checkCubeOverlap(ul1, br1, ul2, br2) || checkCubeOverlap(ul2, br2, ul1, br1);
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
        cout << (checkCubeOverlap(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
