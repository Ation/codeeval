#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printReverseWords( const string &line) {
    int position = line.length() - 1;
    char *str = const_cast<char*>(line.c_str());

    while (position >= 0) {
        // find end of the word
        while (str[position] == ' ') {
            str[position] = 0;
            position--;
        }

        // find begining of the word
        for (; position > 0; position--) {
            if (str[position] == ' ') {
                position++;
                break;
            }
        }

        cout << &(str[position]) << " ";
        position--;
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
        printReverseWords(inputLine);
    }

    return 0;
}
