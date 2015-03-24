#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

void print_line( const string& line) {
    vector<string> words;

    unsigned int position = 0;
    unsigned int start = 0;

    while (position < line.length() ) {
        if ( line[position] == ' ') {
            words.emplace_back( line.substr( start, position - start) );
            ++position;
            start = position;
        } else {
            ++position;
        }
    }

    words.emplace_back( line.substr( start, position - start ) );

    unsigned int total_length = 0;

    position = 0;
    start = 0;

    while (position < words.size() ) {
        if (total_length + (position - start) + words[position].length() > 80 ) {
            unsigned int words_count = position - start;

            if (words_count > 1 ) {
                unsigned int spaces_count = words_count - 1;
                unsigned int total_spaces = 80 - total_length;

                unsigned int spaces_length = total_spaces / spaces_count;
                unsigned int first_spaces_length = total_spaces % spaces_count;

                for (unsigned int i = start; i < position; ++i) {
                    cout << words[i];
                    if ( i != position - 1) {
                        unsigned int to_print = spaces_length;
                        if (first_spaces_length != 0) {
                            to_print++;
                            first_spaces_length--;
                        }
                        for (unsigned int si = 0; si < to_print; ++si) {
                            cout << ' ';
                        }
                    }
                }
            } else {
                cout << words[start];
            }

            cout << endl;

            start = position;
            total_length = words[position].length();

            position++;
        } else {
            total_length += words[position].length();
            position++;
        }
    }

    for (unsigned int i = start; i < position; ++i) {
        cout << words[i];
        if (i != position - 1) {
            cout << ' ';
        }
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
        print_line( inputLine);
    }

    return 0;
}
