#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <list>

using namespace std;

int getDistanceToCity(const string &line, size_t &position) {
    int result = 0;

    for (; position < line.length(); position++) {
        if (line[position] == ',') {
            position++;
            break;
        }
    }

    for (; position < line.length(); position++) {
        if (line[position] == ';') {
            position++;
            break;
        }

        result = result * 10 + (line[position] - '0');
    }

    return result;
}

void printDistances(const string &line) {
    int distance = 0;
    size_t  position = 0;

    list<int>   distane_list;


    while (position < line.length()) {
        distance = getDistanceToCity(line, position);

        distane_list.push_back(distance);
    }

    distane_list.sort();

    distance = 0;

    for (auto i = distane_list.begin(); i != distane_list.end(); ++i) {
        if (distance == 0) {
            cout << (*i);
        } else {
            cout << ',' << (*i) - distance;
        }
        distance = (*i);
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
        printDistances(inputLine);
    }

    return 0;
}
