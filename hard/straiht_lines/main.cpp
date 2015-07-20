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

    friend bool operator == (const Line& left, const Line &right);

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


bool operator == (const Line &left, const Line &right) {
    return
        left._any_y == right._any_y &&
        left._any_x == right._any_x &&
        left._x0 == right._x0 &&
        left._y0 == right._y0;
}

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

    int get_x() const { return _x; }
    int get_y() const { return _y; }

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

class LineFunction {
public:
    LineFunction(const Point &p1, const Point &p2)
      : _any_x(false), _any_y(false), _x(0), _x_add(0) {
        double dx = p2.get_x() - p1.get_x();
        double dy = p2.get_y() - p1.get_y();

        if (dx == 0) {
            _any_y = true;
            _x = p1.get_x();
        } else if (dy == 0) {
            _any_x = true;
            _x_add = p1.get_y();
        } else {
            _x = dy / dx;
            _x_add = p1.get_y() - p1.get_x() * _x;
        }
    }

    bool point_on_line(const Point& p) {
        if (_any_y) {
            return p.get_x() == _x;
        }
        if (_any_x) {
            return p.get_y() == _x_add;
        }
        double y = _x * p.get_x() + _x_add;
        return y == p.get_y();
    }

    friend bool operator == ( const LineFunction& left, const LineFunction &right);

private:
    bool _any_x;
    bool _any_y;

    double _x;
    double _x_add;
};

bool operator == ( const LineFunction& left, const LineFunction &right) {
    return
        left._any_x == right._any_x &&
        left._any_y == right._any_y &&
        left._x == right._x &&
        left._x_add == right._x_add;
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

unsigned int count_direct(const string& line) {
    vector<Point> points;
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

    vector<LineFunction> lines;

    for (unsigned int first = 0; first < points.size() - 2; first++) {
        for (unsigned int second = first + 1; second < points.size() - 1; second++) {
            LineFunction line_function(points[first], points[second]);

            bool line_exists = false;
            for ( auto &lines_item : lines) {
                if (line_function == lines_item) {
                    line_exists = true;
                    break;
                }
            }

            if (line_exists) {
                continue;
            }

            for (unsigned int third = second + 1; third < points.size(); third++) {
                if (line_function.point_on_line(points[third]) ) {
                    lines.emplace_back( move(line_function));
                    break;
                }
            }
        }
    }

    return lines.size();
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
