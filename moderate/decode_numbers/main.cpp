#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Fiboner {
public:
    Fiboner() : m_values( { 1, 1, 2, 3, 5}) {
    }

    int get(unsigned int index) {
        while (index >= m_values.size())
        {
            const int last_index = m_values.size() - 1;
            m_values.push_back( m_values[last_index] + m_values[last_index - 1] );
        }

        return m_values[index];
    }
private:
    vector<int> m_values;
};

Fiboner f;

unsigned int getDecodeCount(const string &line) {
    if (line.length() == 1) {
        return 1;
    }

    unsigned int result = 1;
    unsigned int comb_count = 0;

    for (unsigned int i=0; i < line.length(); i++) {
        if (line[i] > '2') {
            if (comb_count == 0) {
                continue;
            }

            if (line[i-1] != '2' || (line[i] <= '6')) {
                comb_count++;
            }

            int combo = f.get(comb_count);
            if (result != 0) {
                result *= combo;
            } else {
                result = combo;
            }
            comb_count = 0;
        } else if (line[i] == '0') {
            int combo = f.get(comb_count-1);
            if (result != 0) {
                result *= combo;
            } else {
                result = combo;
            }
            comb_count = 0;
        } else {
            comb_count++;
        }
    }

    if (comb_count != 0) {
        int combo = f.get(comb_count);
        if (result != 0) {
            result *= combo;
        } else {
            result = combo;
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
        cout << getDecodeCount(inputLine) << endl;
    }

    return 0;
}
