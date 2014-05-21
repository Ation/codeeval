#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

bool isArmstrong(const string &line) {
    if (line.length() == 1) {
        return true;
    }

    unsigned int number = 0;
    unsigned int sum = 0;
    unsigned int digit;
    unsigned int power_result;
    const unsigned int power = line.length();
    for (auto && symbol : line) {
        digit = symbol - '0';
        number = number * 10 + digit;

        power_result = 1;
        for (int i=0; i < power; i++) {
            power_result *= digit;
        }

        sum += power_result;
    }

    return sum == number;
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
        cout << (isArmstrong(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
