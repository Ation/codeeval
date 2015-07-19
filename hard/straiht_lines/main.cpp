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

class Line {
public:
    Line(double x0, double y0) : _any_x(false), _any_y(false), _x0(x0), _y0(y0) {}

    Line(bool, double y0) : _any_x(true), _any_y(false), _x0(0), _y0(y0) {}

    Line(double x0, bool) : _any_x(false), _any_y(true), _x0(x0), _y0(0) {}

    bool operator < (const Line& other) const {
        if (_any_x == other._any_x) {
            if (_x0 != other._x0) {
                return _x0 < other._x0;
            }

            if (_any_y == other._any_y) {
                return _y0 < other._y0;
            } else {
                return _any_y;
            }
        } else {
            return _any_x;
        }
    }

private:
    double _x0;
    double _y0;

    bool _any_x;
    bool _any_y;
};


class Point {
public:
    Point(int x, int y) : _x(x), _y(y) {}

    Line create_line(const Point& other) const {
        if (_x == other._x) {
            // cout << "Create X line : " << _x << endl;
            return Line(_x, true);
        }

        if (_y == other._y) {
            // cout << "Create Y line: " << _y << endl;
            return Line(true, _y);
        }

        double x0 = get_x0(other);
        double y0 = get_y0(other);

        // cout << "Create XY line : " << x0 << ',' << y0 << endl;
        return Line(x0, y0);
    }

    friend bool operator == ( const Point& left, const Point& right);

private:
    const int _x;
    const int _y;

    double get_x0(const Point& other) const {
        return _x - static_cast<double>(_y * ( other._x - _x)) / (other._y - _y);
    }

    double get_y0(const Point& other) const {
        return _y - static_cast<double>(_x * (other._y - _y)) / (other._x - _x);
    }
};

bool operator == ( const Point& left, const Point& right) {
    return left._x == right._x && left._y == right._y;
}

unsigned int count_lines(const string& line) {
    unsigned int result = 0;

    vector<Point> points;
    map<Line, unsigned int> lines;
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

        Point new_point(x, y);

        for ( auto &p : points) {
            auto line = new_point.create_line(p);
            auto i = lines.find(line);
            if (i == lines.end()) {
                lines.emplace_hint(i, line, 2);
            } else {
                i->second += 1;
            }
        }

        points.emplace_back(move(new_point));
    } while(true);

    for (auto &i : lines) {
        if (i.second >= 3) {
            ++result;
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
        cout << count_lines(inputLine) << endl;
    }

    return 0;
}
