#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool getInteger(const string &line, size_t &position, int &number) {
    int result = 0;
    bool negative = false;

    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp == '-') {
            negative = true;
            position++;
            break;
        }
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
            position++;
            break;
        }
    }

    if (negative) {
        result = -result;
    }
    number = result;
    return true;
}
class JollyContainer {
public:
    JollyContainer() {}

    void reset() {
        memset(m_jumps, 0, sizeof(m_jumps));
        m_jumpsNumber = 0;
		m_length.clear();
    }

    bool jump(unsigned int length) {
		if (length == 0) {
			return false;
		}
        unsigned int index = (length -1) / 8;
        unsigned int mask = 1 << ((length - 1) & 0x07);

        if (m_jumps[index] & mask) {
            return false;
        }

        m_jumps[index] |= mask;
        m_jumpsNumber++;

		m_length.push_back(length);

        return true;
    }

    bool wasJolly() {
		sort(m_length.begin(), m_length.end());

        unsigned int index = m_jumpsNumber / 8;
        unsigned int lastMask = ~( ( (unsigned int)-1) << ( m_jumpsNumber & 7 ) );

        const unsigned char setMask = 0xff;

        for (unsigned int i=0;  i < index; i++) {
            if (m_jumps[i] != setMask) {
                return false;
            }
        }

        if (m_jumps[index] != lastMask) {
            return false;
        }

        return true;
    }

private:
    unsigned char    m_jumps[375];
    int     m_jumpsNumber;
	vector<unsigned int> m_length;
};

bool isJolly(const string &line, JollyContainer *jc) {
    int last;
    int current;
    int length;
    int max;

    size_t position = 0;

    jc->reset();

    getInteger(line, position, max);
    getInteger(line, position, last);

    while (getInteger(line, position, current)) {
        length = current - last;
        if (length < 0) {
            length = -length;
        }

        if (max < length) {
            return false;
        }

        last = current;

        if (!jc->jump(length)) {
            return false;
        }
    }

    return jc->wasJolly();
}

int main(int argc, char *argv[]) {
	JollyContainer  *jc = new JollyContainer();

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        cout << (isJolly(inputLine, jc) ? "Jolly" : "Not jolly" ) << endl;
    }

    return 0;
}
