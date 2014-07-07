#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unordered_map>

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
            break;
        }
    }

    number = result;
    return true;
}

class Inspector {
public:
    Inspector() : m_start(-1), m_end(-1) {}

    bool isValid(const string &line) {
        // add elements
        size_t position = 0;
        unsigned int left;
        unsigned int right;
        while (position < line.length()) {
            if (line[position] == 'B') {
                if (m_start != -1) {
                    return false;
                }
                getUnsignedInteger(line, position, left);
                m_start = left;

            } else {
                getUnsignedInteger(line, position, left);
                position++;

                if (line[position] == 'E') {
                    if (m_end != -1) {
                        return false;
                    }
                    m_end = left;
                } else {
                    getUnsignedInteger(line, position, right);

                    if (m_elements.find(left) != m_elements.end()) {
                        return false;
                    }

                    m_elements.emplace(left, right);
                }
            }

            while (position < line.length() && line[position] != ';') {
                position++;
            }
            position++;
        }

        if ((m_end == -1) || (m_start == -1)) {
            return false;
        }

        unsigned int count = 0;
        unsigned int index = m_start;

        while ((index != m_end) && (count <= m_elements.size())) {
            auto it = m_elements.find(index);
            if (it == m_elements.end()) {
                return false;
            }
            index = it->second;
            count++;
        }

        return count == m_elements.size();
    }

private:
    int m_start;
    int m_end;

    unordered_map<unsigned int, unsigned int> m_elements;
};

bool inspectChain(const string &line) {
    Inspector inspector;

    return inspector.isValid(line);
}

bool paranoidInspection(const string &line) {
    unordered_map<unsigned int, unsigned int> forward;
    unordered_map<unsigned int, unsigned int> backward;
    unsigned int m_start = -1;
    unsigned int m_end = -1;

    size_t position = 0;
    unsigned int left;
    unsigned int right;

    while (position < line.length()) {
        if (line[position] == 'B') {
            if (m_start != -1) {
                return false;
            }
            getUnsignedInteger(line, position, left);
            m_start = left;

        } else {
            getUnsignedInteger(line, position, left);
            position++;

            if (line[position] == 'E') {
                if (m_end != -1) {
                    return false;
                }
                m_end = left;
            } else {
                getUnsignedInteger(line, position, right);

                if (forward.find(left) != forward.end()) {

                    return false;
                }
                if (backward.find(right) != backward.end()) {
                    return false;
                }

                forward.emplace(left, right);
                backward.emplace(right, left);
            }
        }

        while (position < line.length() && line[position] != ';') {
            position++;
        }
        position++;
    }

    if ((m_end == -1) || (m_start == -1)) {
        return false;
    }

    unsigned int count = 0;
    unsigned int index = m_start;

    while ((index != m_end) && (count <= forward.size())) {
        auto it = forward.find(index);
        if (it == forward.end()) {
            return false;
        }
        index = it->second;
        count++;
    }

    if (count != forward.size()) {
        return false;
    }

    count = 0;
    index = m_end;

    while ((index != m_start) && (count <= backward.size())) {
        auto it = backward.find(index);
        if (it == backward.end()) {
            return false;
        }
        index = it->second;
        count++;
    }

    return count == backward.size();
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
        cout << (inspectChain(inputLine) ? "GOOD" : "BAD") << " " << (paranoidInspection(inputLine) ? "GOOD" : "BAD") << endl;
    }

    return 0;
}
