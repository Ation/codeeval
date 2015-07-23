#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

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

class ABlock {
public:
    ABlock(const string &line, size_t start_position) : _line(line), _start(start_position), _used(false) {}

    bool contains(const char c) const {
        for (size_t i = _start; i < _start + 6; ++i) {
            if (_line[i] == c) {
                return true;
            }
        }

        return false;
    }

    bool is_used() const {
        return _used;
    }

    void set_usage(bool is_used) {
        _used = is_used;
    }

    void swap(ABlock &other) {
        size_t temp = _start;
        _start = other._start;
        other._start = temp;
    }
private:
    const string &_line;
    size_t _start;

    bool _used;
};

class Blocker {
public:
    Blocker() {}

    bool create_word(const string &line) {
        size_t position = 0;
        _str = line.c_str();

        unsigned int blocks_count = getUnsignedInteger(line, position);

        _blocks.clear();
        _blocks.reserve( blocks_count );

        _word_start = position + 2;

        for (position=_word_start; line[position] != ' '; ++position) {
            //empty loop
        }

        position += 3;
        for (unsigned int i=0; i < blocks_count; ++i, position += 7) {
            _blocks.emplace_back(line, position);
        }

        return is_possible_to_create(_word_start);
    }
private:
    vector<ABlock>  _blocks;
    unsigned int    _word_start;
    const char      *_str;

    bool is_possible_to_create(int word_index) {
        if (_str[word_index] == ' ') {
            return true;
        }

        for (int i=0; i < _blocks.size(); ++i) {
            if (_blocks[i].contains(_str[word_index]) && !_blocks[i].is_used()) {
                _blocks[i].set_usage(true);
                if (is_possible_to_create(word_index+1)) {
                    return true;
                }
                _blocks[i].set_usage(false);
            }
        }

        return false;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    Blocker b;

    while ( getline(inFile, inputLine)) {
        cout << (b.create_word(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
