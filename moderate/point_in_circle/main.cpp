#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

typedef struct __point {
    double x;
    double y;
}Point;

double readDouble(const string &line, size_t &position) {
    double result = 0;
    bool negative = false;
    char temp;

    for (;position < line.length(); position++) {
        temp = line[position];

        if (temp == '-' || (temp >= '0' && temp <= '9')) {
            break;
        }
    }

    if (temp == '-') {
        negative = true;
        position++;
    }

    for (; position < line.length(); position++) {
        temp = line[position];

        if (temp == '.') {
            position++;
            int mult = 10;

            for (; position < line.length(); position++) {
                temp = line[position];
                if (temp < '0' || temp > '9') {
                    break;
                }

                result = result + ((double)(temp - '0'))/mult;
                mult *= 10;
            }

            break;
        } else if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            break;
        }
    }

    if (negative) {
        result = -result;
    }

    return result;
}

Point readPoint(const string &line, size_t &position) {
    double x = readDouble(line, position);
    double y = readDouble(line, position);

    return { x, y};
}

bool isInside(const string &line) {
    size_t position = 0;
    Point center =  readPoint(line, position);
    double radius = readDouble(line, position);

    Point point = readPoint(line, position);

    double diff = center.x - point.x;
    double distance = center.y - point.y;

    distance = sqrt(distance * distance + diff * diff);

    return distance <= radius;
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
		cout << (isInside(inputLine) ? "true" : "false") << endl;
    }

    return 0;
}
