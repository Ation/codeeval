#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class RevAdd {
public:
    RevAdd(const string &line) : m_count(0) {
        m_value.resize( line.length() );
        for (int i=0; i < line.length(); ++i) {
            m_value[i] = (line[ i ] - '0' );
        }

        m_isPalindrome = checkIsPalindrome();
    }

    bool isPalindrome() const {
        return m_isPalindrome;
    }

    void ReverseAdd() {
        m_count++;
        for (int i=0, j=m_value.size() - 1; i <= j; ++i, --j) {
            m_value[i] = m_value[j] = m_value[i] + m_value[j];
        }

        int left = 0;
        m_isPalindrome = true;


        for (int i=0; i < m_value.size(); i++) {
            m_value[i] += left;

            if (m_value[i] > 9) {
                left = m_value[i] / 10;
                m_value[i] %= 10;
                m_isPalindrome = false;
            } else {
                left = 0;
            }
        }

        if (left != 0) {
            m_value.push_back(left);
        }
    }

    int reverseCount() const {
        return m_count;
    }

    void print() {
        cout << m_count << ' ';

        for (auto i= m_value.begin(); i != m_value.end(); ++i) {
            cout << (*i);
        }

        cout << endl;
    }

private:
    int         m_count;
    vector<int> m_value;
    bool        m_isPalindrome;

    bool checkIsPalindrome() const {
        for (int i=0, j=m_value.size() - 1; i < j; i++, j--) {
            if (m_value[i] != m_value[j]) {
                return false;
            }
        }
        return true;
    }
};

void printPalindrome(const string &line) {
    RevAdd ra(line);

    while ( !ra.isPalindrome() ) {
        ra.ReverseAdd();

        if (ra.reverseCount() > 100) {
            cout << "ERROR" << endl;
            return;
        }
    }

    ra.print();

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
        printPalindrome(inputLine);
    }

    return 0;
}
