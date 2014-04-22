#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

unsigned int getInteger(const string &line) {
    unsigned int result = 0;

    for (size_t i = 0 ; i < line.length(); ++i) {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}

unsigned long long getFibonacci(const string &line) {
    unsigned int index = getInteger(line);
    unsigned long long number = 0;

    unsigned long long left;
    unsigned long long right;

    if (index == 0) {
        return 0;
    }

    if (index < 3) {
        return 1;
    }

    left = 1;
    right = 1;
    number = 2;

    for (unsigned int i=2; i < index; i++) {
        number = left + right;
        left = right;
        right = number;
    }

    return number;
}

unsigned long long getCombinationsCount(const string &line) {
    unsigned long long result = 0;

    unsigned int stairs_cout = getInteger(line);
    unsigned long long fib = getFibonacci(stairs_cout + 1);

    unsigned int two_count = stairs_cout / 2;
    unsigned int one_count = stairs_cout & 1;

    unsigned long long last_group;

    if (one_count == 0) {
        result = last_group = 1;
    } else {
        result = last_group = one_count + two_count;
    }

    while (two_count != 0) {
        last_group *= two_count;

        one_count ++;
        last_group *= (one_count + two_count);

        two_count--;
        last_group /= one_count;
        one_count++;
        last_group /= one_count;

        result += last_group;
    }

    if (result != fib) {
        cout << fib << ':' << result << endl;
    } else {
        cout << result << endl;
    }

    return result;
}

int main(int argc, char *argv[]) {
    getCombinationsCount("774");
    getCombinationsCount("564");
    getCombinationsCount("528");
    getCombinationsCount("28");
    getCombinationsCount("352");
    getCombinationsCount("22");
    getCombinationsCount("205");
    getCombinationsCount("937");
    getCombinationsCount("875");
    getCombinationsCount("253");
    getCombinationsCount("836");
    getCombinationsCount("686");
    getCombinationsCount("10");
    getCombinationsCount("148");
    getCombinationsCount("392");
    getCombinationsCount("250");
    getCombinationsCount("467");
    getCombinationsCount("852");
    getCombinationsCount("999");
    getCombinationsCount("162");

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        getCombinationsCount(inputLine);
    }

    return 0;
}
