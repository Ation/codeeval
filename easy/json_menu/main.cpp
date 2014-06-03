#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

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
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

bool openArray(const string &line, size_t &position) {
    for (; position < line.length(); position++) {
        if (line[position] == '[') {
            position++;
            if (position < line.length()) {
                return true;
            }
            return false;
        }
    }

    return false;
}

bool nextItem(const string &line, size_t &position) {
    for (;position < line.length(); position++) {
        if (line[position] == '{') {
            position++;
            if (position < line.length()) {
                return true;
            }
            return false;
        }
        if (line[position] == ']') {
            return false;
        }
    }

    return false;
}

bool isId(const string &line, size_t position) {
    bool result = true;
    static const string label = "id";

    if (position + label.length() + 1 >= line.length()) {
        return false;
    }

    if (line[position + label.length()] != '\"') {
        return false;
    }

    for (int i=0; i < label.length(); i++) {
        if (label[i] != line[position + i]) {
            result = false;
            break;
        }
    }

    return result;
}

bool isLabel(const string &line, size_t position) {
    bool result = true;
    static const string label = "label";

    if (position + label.length() + 1 >= line.length()) {
        return false;
    }

    if (line[position + label.length()] != '\"') {
        return false;
    }

    for (int i=0; i < label.length(); i++) {
        if (label[i] != line[position + i]) {
            result = false;
            break;
        }
    }

    return result;
}

bool isLabelPresent(const string &line, size_t position) {
    bool result = false;

    for (; position < line.length(); position++) {
        if (line[position] == '}') {
            break;
        }
        if (line[position] == '\"') {
			if (isLabel(line, position + 1)) {
				return true;
			}
        }
    }

    return result;
}

bool getLabel(const string &line, size_t &position, unsigned int &label) {
    unsigned int id = 0;

    if (isLabelPresent(line, position)) {
        for (; position < line.length(); position++) {
            if (line[position] == '\"') {
                position++;
                if (isId(line, position)) {
                    if (getUnsignedInteger(line, position, id)) {
                        label = id;
                        return true;
                    }

                    return false;
                }
            }
        }
    }

    return false;
}

unsigned int sumOfLabels(const string &line) {
    unsigned int sum = 0;
    size_t position = 0;
    unsigned int label;

    if (!openArray(line, position)) {
        return 0;
    }

    while (nextItem(line, position)) {
        if (getLabel(line, position, label)) {
            sum += label;
        }
    }

    return sum;
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
        cout << sumOfLabels(inputLine) << endl;
    }

    return 0;
}
