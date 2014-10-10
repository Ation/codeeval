#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

class WordChain {
public:
    WordChain() : m_longestChain(1) {

    }

    WordChain( const WordChain &) = delete;

    bool addWord( const string &&word) {
        if ( word.empty() ) {
            return false;
        }
        cout << word << endl;
        return true;
    }

    unsigned int getLongestChain() const {
        return m_longestChain;
    }

private:
    unsigned int m_longestChain;
};

string getWord( const string &line, size_t &start) {
    if (start >= line.length()) {
        return string();
    }
    size_t begin = start;
    size_t end = start;

    while (end < line.length() ) {
        if (line[end] == ',') {
            break;
        }
        end++;
    }

    start = end + 1;
    return line.substr(begin, end - begin);
}

void process_words( const string &line ) {
    WordChain wc;
    size_t start = 0;

    while ( wc.addWord( getWord(line, start) ) ) {}

    unsigned int length = wc.getLongestChain();
    if (length <= 1) {
        cout << "None" << endl;
    } else {
        cout << length << endl;
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
        process_words( inputLine );
    }

    return 0;
}
