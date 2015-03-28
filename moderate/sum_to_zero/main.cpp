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

int get_sum(vector<int>& numbers, unsigned int l1, unsigned int l2, unsigned int r1, unsigned int r2) {
    return numbers[l1] + numbers[l2] + numbers[r1] + numbers[r2];
}

// to few elements in input array to bother
unsigned int straight_count( const vector< int> &numbers) {
    unsigned int i1 = 0;
    unsigned int i2 = 1;
    unsigned int i3 = 2;
    unsigned int i4 = 3;

    unsigned int result = 0;

    for( unsigned int i1 = 0; i1 < numbers.size() - 3; i1++) {
        for( unsigned int i2 = i1 + 1; i2 < numbers.size() - 2; i2++) {
            for( unsigned int i3 = i2 + 1; i3 < numbers.size() - 1; i3++) {
                for( unsigned int i4 = i3 + 1; i4 < numbers.size() ; i4++) {
                    if ( numbers[i1] + numbers[i2] + numbers[i3] + numbers[i4] == 0) {
                        result++;
                    }
                }
            }
        }
    }

    return result;
}

void procecc_line( const string &line) {
    unsigned int straight_ways_count = 0;
    vector<int> numbers;

    size_t position = 0;
    while ( position < line.length() ) {
        numbers.emplace_back( getInteger( line, position ));
    }

    straight_ways_count = straight_count(numbers);

    cout << straight_ways_count << endl;
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
        procecc_line( inputLine);
    }

    return 0;
}
