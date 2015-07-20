#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;


int getInteger(const string &line, size_t &position) {
    int result = 0;
    bool negative = false;
    char temp;

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

void print_direction( const string& line) {
    size_t position = 0;

    int observer_x = getInteger(line, position);
    int observer_y = getInteger(line, position);

    int destination_x = getInteger(line, position);
    int destination_y = getInteger(line, position);

    bool same_position = true;

    if (observer_y < destination_y) {
        cout << 'N';
        same_position = false;
    } else if (observer_y > destination_y) {
        cout << 'S';
        same_position = false;
    }

    if (observer_x < destination_x) {
        cout << 'E';
        same_position = false;
    } else if (observer_x > destination_x) {
        cout << 'W';
        same_position = false;
    } else if (same_position) {
        cout << "here";
    }

    cout << endl;
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
        print_direction( inputLine);
    }

    return 0;
}
