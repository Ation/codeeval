#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool find_pattern( const string& source, unsigned int &position, const string &pattern) {
    for (; position + pattern.length() <= source.length(); position++) {
        bool differ = false;

        for (unsigned int i = 0; i < pattern.length(); i++) {
            if (pattern[i] != source[position + i]) {
                differ = true;
                break;
            }
        }

        if ( !differ) {
            position += pattern.length();
            return true;
        }
    }

    return false;
}

bool contain_patterns( const string& source, const vector<string> &patterns) {
    unsigned int position = 0;

    for(auto&& pattern : patterns) {
        if ( ! find_pattern(source, position, pattern) ) {
            return false;
        }
    }

    return true;
}

bool substring_exists( const string &line) {
    vector<string> patterns;
    string single_pattern;
    string source;

    unsigned int i;

    for (i=0; i< line.length(); i++) {
        if (line[i] == ',') {
            break;
        }
    }

    source = line.substr(0, i);
    single_pattern.reserve(line.length()  - i + 1);

    unsigned int pattern_start = i + 1;
    while (pattern_start < line.length() ) {
        for (; pattern_start < line.length(); pattern_start++) {
            if (line[pattern_start] == '*') {
                pattern_start++;
                break;
            }
            if (line[pattern_start] == '\\') {
                // could be escape symbol
                if (pattern_start + 1 < line.length()) {
                    if (line[pattern_start + 1] == '*') {
                        pattern_start++;
                    }
                }
            }

            single_pattern.push_back( line[pattern_start] );
        }

        if ( !single_pattern.empty() ) {
            patterns.push_back(single_pattern);
            single_pattern.clear();
        }
    }

    return contain_patterns(source, patterns);
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
        cout << ( substring_exists(inputLine) ? "true" : "false") << endl;
    }

    return 0;
}
