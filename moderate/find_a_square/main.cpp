#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
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

    return result;
}

struct Point {
    unsigned int x;
    unsigned int y;
};

bool x_compare (const Point& left, const Point& right) {
    if (left.x == right.x) {
        return left.y < right.y;
    }
    return left.x < right.x;
}

Point readPoint(const string &line, size_t &position) {
    unsigned int x = getUnsignedInteger(line, position);
    unsigned int y = getUnsignedInteger(line, position);

    return {x, y};
}

int diff_x(const Point &p1, const Point &p2) {
    return p1.x - p2.x;
}

int diff_y(const Point &p1, const Point &p2) {
    return p1.y - p2.y;
}

bool isCubeLine(const string &line) {
    vector<Point> x_axis;
    size_t position = 0;

    x_axis.emplace_back( readPoint(line, position) );
    x_axis.emplace_back( readPoint(line, position) );
    x_axis.emplace_back( readPoint(line, position) );
    x_axis.emplace_back( readPoint(line, position) );

    sort(x_axis.begin(), x_axis.end(), x_compare);

    if (x_axis[0].x == x_axis[1].x) {
        if (x_axis[2].x != x_axis[3].x) {
            return false;
        }
        if (x_axis[0].y != x_axis[2].y) {
            return false;
        }
        if (x_axis[1].y != x_axis[3].y) {
            return false;
        }
        if (x_axis[0].x == x_axis[2].x) {
            return false;
        }
    } else {
        const int diff_1 = diff_x( x_axis[1], x_axis[0]);
        const int diff_2 = diff_x( x_axis[3], x_axis[1]);

        if ( diff_1 != diff_x(x_axis[3], x_axis[2]) ) {
            return false;
        }

        if ( diff_2 != diff_x(x_axis[2], x_axis[0]) ) {
            return false;
        }

        if (x_axis[1].y > x_axis[3].y) {
            if ( diff_1 != diff_y(x_axis[0], x_axis[2]) ) {
                return false;
            }

            if ( diff_1 != diff_y(x_axis[1], x_axis[3]) ) {
                return false;
            }

            if ( diff_2 != diff_y(x_axis[1], x_axis[0]) ) {
                return false;
            }

            if ( diff_2 != diff_y(x_axis[3], x_axis[2]) ) {
                return false;
            }
        } else {
            if ( diff_1 != diff_y(x_axis[2], x_axis[0]) ) {
                return false;
            }

            if ( diff_1 != diff_y(x_axis[3], x_axis[1]) ) {
                return false;
            }

            if ( diff_2 != diff_y(x_axis[0], x_axis[1]) ) {
                return false;
            }

            if ( diff_2 != diff_y(x_axis[2], x_axis[3]) ) {
                return false;
            }
        }
    }

    return true;
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
        cout << ( isCubeLine(inputLine) ? "true" : "false") << endl;
    }

    return 0;
}
