#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    unsigned int result = 0;
    char temp;
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

unsigned int processNumer(unsigned int number) {
    unsigned int  result = 0;

    unsigned int  temp;

    while (number != 0) {
        temp = number % 10;
        result += temp * temp;

        number /= 10;
    }

    return result;
}

class Set100Bytes {
public:
    Set100Bytes() {
		memset(m_fields, 0, 22);
    }

    void set(unsigned int index) {
        int bucket = index >> 3;
        int mask = (1 << (index & 7));

        m_fields[bucket] |= mask;
    }

    bool isSet(unsigned int index) {
        int bucket = index >> 3;
        int mask = (1 << (index & 7));

        return (m_fields[bucket] & mask) != 0;
    }

private:
    char m_fields[22];
};

int isHappy(const string &line) {
    Set100Bytes   numbers_set;

    int result = 1;
    size_t position = 0;

    unsigned int number = getUnsignedInteger(line, position);

    while (number > 100) {
        number = processNumer(number);
    }

    while (number != 1) {
        if (numbers_set.isSet(number)) {
            result = 0;
            break;
        }
        numbers_set.set(number);
        number = processNumer(number);
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
        cout << (isHappy(inputLine) ? '1' : '0') << endl;
    }

    return 0;
}
