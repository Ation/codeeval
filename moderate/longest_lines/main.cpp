#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <set>

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

class LongestStringStorage {
public:
    LongestStringStorage(unsigned int size) : m_count(size) {
    }

    void moveStringToStorage(string &line) {
        if (m_strings.size() < m_count) {
            m_strings.insert(move(line));
        } else {
            auto first = m_strings.begin();

            if ((*first).length() < line.length()) {
                m_strings.erase(first);
                m_strings.insert(move(line));
            }
        }
    }


    void printStrings() const {
        for (auto i = m_strings.rbegin(); i != m_strings.rend(); ++i) {
            cout << (*i) << endl;
        }
    }

private:
    struct string_compare {
        bool operator() (const string& left, const string& right) {
            return left.length() < right.length();
        }
    };

    set<string, string_compare> m_strings;
    unsigned int m_count;
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

    // read count
    if (!getline(inFile, inputLine)) {
        return 1;
    }

    size_t position = 0;
    unsigned int max_count = getUnsignedInteger(inputLine, position);

    // init storage
    LongestStringStorage    storage(max_count);

    // read lines
    while ( getline(inFile, inputLine)) {
        // insert line to storage
        storage.moveStringToStorage(inputLine);
    }

    // print sorted
    storage.printStrings();

    return 0;
}
