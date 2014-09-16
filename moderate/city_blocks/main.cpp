#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

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
            break;
        }
    }

    number = result;
    return true;
}

double get_av_distance( unsigned int street, unsigned int max_street, unsigned int max_avenue) {
    double result = street;

    return result * max_avenue / max_street;
}

unsigned int count_blocks( const string &line) {
    vector<unsigned int> streets;
    vector<unsigned int> avenues;

    streets.reserve(100);
    avenues.reserve(100);

    unsigned int result = 0;
    size_t position = 0;
    unsigned int temp;

    //read streets
    while (line[position] != ')') {
        getUnsignedInteger( line, position, temp);
        streets.emplace_back( temp );
    }

    // read avenues
    while ( getUnsignedInteger(line, position, temp) ) {
        avenues.emplace_back( temp );
    }

    unsigned int max_street = streets[ streets.size() - 1 ];
    unsigned int max_avenue = avenues[ avenues.size() - 1 ];

    unsigned int is = 1;
    unsigned int ia = 1;

    double distance = get_av_distance( streets[is], max_street, max_avenue );

    while ( ia < avenues.size() ) {
        result++;
        if (avenues[ia] < distance ) {
            ia++;
        } else {
            if (avenues[ia] == distance) {
                ia++;
            }
            is++;
            if (is == streets.size() ) {
                break;
            }
            distance = get_av_distance( streets[is], max_street, max_avenue );
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
        cout << count_blocks( inputLine ) << endl;
    }

    return 0;
}
