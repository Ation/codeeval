#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

static const unsigned int distance_to_wall = 6;

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

unsigned int getAdditionalBats(const string &line) {
    unsigned int result = 0;
    size_t position = 0;

    unsigned int length;
    unsigned int distance;
    unsigned int count;

    getUnsignedInteger(line, position, length);
    getUnsignedInteger(line, position, distance);
    getUnsignedInteger(line, position, count);

    if (length < (distance_to_wall * 2) ) {
        return 0;
    }

    if (count == 0) {
        return ((length - (distance_to_wall * 2) )/distance) + 1;
    } else {
        vector<unsigned int> positions;
        positions.reserve(count);
        unsigned int left;
        unsigned int right;

        while ( getUnsignedInteger(line, position, left) ) {
            positions.push_back(left);
        }

        sort(positions.begin(), positions.end());

        // to wall from left
        left = distance_to_wall;
        right = positions[0];

        result += (right - left) / distance;

        // to wall from right
        left = positions[positions.size() - 1];
        right = length - distance_to_wall;

        result += (right - left) / distance;

        for (unsigned int i = 1; i < positions.size(); i++) {
            left = positions[i-1];
            right = positions[i];

            if (right >= left + distance * 2) {
                result += (right - left - distance) / distance;
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

    while ( getline(inFile, inputLine) ) {
        cout << getAdditionalBats(inputLine) << endl;
    }

    return 0;
}
