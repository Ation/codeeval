#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool getInteger(const string &line, size_t &position, int &number) {
    int result = 0;
    bool negative = false;
    char temp;

    for (; position < line.length(); ++position) {
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
struct __point_coordinates {
    int x;
    int y;

    __point_coordinates(int _x, int _y) : x(_x), y(_y){}
};

using Point = struct __point_coordinates;

double get_dx(const Point& p1, const Point &p2) {
    return p1.x - p2.x;
}

double get_dy(const Point& p1, const Point &p2) {
    return p1.y - p2.y;
}

unsigned int count_direct(const string& line) {
    static vector<Point> points;
    points.clear();

    size_t position = 0;

    do {
        int x;
        int y;

        if (!getInteger(line, position, x)) {
            break;
        }
        if (!getInteger(line, position, y)) {
            break;
        }

        points.emplace_back(x, y);
    } while (true);

    unsigned int result = 0;
    unsigned int points_count = points.size();

    for (unsigned int first = 0; first < points_count - 2; first++) {
        for (unsigned int second = first + 1; second < points_count - 1; second++) {
            double dx = get_dx(points[first], points[second]);
            double dy = get_dy(points[first], points[second]);

            for (unsigned int third = 0; third < points_count; ++third) {
                if ( (third != first)
                  && (third != second)
                  && (dx * get_dy(points[first], points[third]) == dy * get_dx(points[first], points[third])) ) {
                    if (third > second) {
                        ++result;
                    }
                    break;
                }
            }
        }
    }

    return result;
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
        cout << count_direct(inputLine)  << endl;
    }

    return 0;
}
