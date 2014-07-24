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

class TrianglePath {
public:
    explicit TrianglePath(const int size) {
        m_values.reserve(size);
    }

    TrianglePath() {}

    TrianglePath(const TrianglePath&) = delete;

    void addLine(const string &line) {
        size_t position = 0;
        unsigned int saved_value;
        unsigned int next_value;
        unsigned int next_saved;

        unsigned int left_sum;
        unsigned int right_sum;

        getUnsignedInteger(line, position, next_value);

        if (m_values.empty()) {
            m_values.push_back(next_value);
            return;
        }

        saved_value = m_values[0];
        m_values[0] = saved_value + next_value;

        for (unsigned int i=1; i < m_values.size(); i++) {
            getUnsignedInteger(line, position, next_value);
            next_saved = m_values[i];

            left_sum = saved_value + next_value;
            right_sum = next_saved + next_value;

            m_values[i] = (left_sum > right_sum ? left_sum : right_sum);
            saved_value = next_saved;
        }

        getUnsignedInteger(line, position, next_value);
        m_values.push_back(saved_value + next_value);
    }

    unsigned int getMaxPath() const {
        unsigned int result = m_values[0];

        for (unsigned int i = 1; i < m_values.size(); i++) {
            if (m_values[i] > result) {
                result = m_values[i];
            }
        }

        return result;
    }
private:
    vector<unsigned int> m_values;
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

    TrianglePath    path(100);

    while ( getline(inFile, inputLine)) {
        path.addLine(inputLine);
    }

    cout << path.getMaxPath() << endl;

    return 0;
}
