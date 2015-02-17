#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void goto_end(const string &line, size_t &position) {
    while (position < line.length() ) {
        if ( line[position] == ',' ) {
            break;
        }
        position++;
    }
}

int count_dots( const string& line, size_t &position) {
    int result = 0;

    while (position < line.length() ) {
        char c = line[position];
        position++;
        if ( c == 'Y') {
            goto_end(line, position);
            return 0;
        }
        if ( c == '.') {
            result = 1;
            break;
        }
    }

    while (position < line.length() ) {
        char c = line[position];
        if ( line[position] == 'Y') {
            break;
        }
        result++;
        position++;
    }

    goto_end(line, position);

    return result;
}

int count_offset( const string &line ) {
    size_t position = 0;
    int result = line.length();

    while ( position < line.length() ) {
        int current = count_dots( line, position);
        if ( current < result) {
            result = current;
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
        cout << count_offset(inputLine) << endl;
    }

    return 0;
}
