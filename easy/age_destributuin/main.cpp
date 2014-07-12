#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

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

void where(const string &line) {
    int age = 0;
    size_t position = 0;

    age = getInteger(line, position);

    if (age < 0) {
        cout << "This program is for humans" << endl;
    } else if (age <= 2) {
        cout << "Home" << endl;
    } else if (age <= 4) {
        cout << "Preschool" << endl;
    } else if (age <= 11) {
        cout << "Elementary school" << endl;
    } else if (age <= 14) {
        cout << "Middle school" << endl;
    } else if (age <= 18) {
        cout << "High school" << endl;
    } else if (age <= 22) {
        cout << "College" << endl;
    } else if (age <= 65) {
        cout << "Work" << endl;
    } else if (age <= 100) {
        cout << "Retirement" << endl;
    } else {
        cout << "This program is for humans" << endl;
    }
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
        where(inputLine);
    }

    return 0;
}
