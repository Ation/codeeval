#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory>

using namespace std;

class WordChain {
public:
    WordChain() : m_longestChain(0), m_defferedCount(0) {
        memset( m_accessMatrix, 0, sizeof m_accessMatrix);
        memset( m_defferedWords, 0, sizeof m_defferedWords);
        memset( m_totalIncome, 0, sizeof m_totalIncome);
    }

    WordChain( const WordChain &) = delete;

    bool addWord( const string &&word) {
        if ( word.empty() ) {
            return false;
        }

        int from = word[0] - 'a';
        int to = word[ word.length() - 1 ] - 'a';

        m_defferedWords[from][to] ++;
        m_defferedCount++;

        if (from != to) {
            m_totalIncome[to]++;
        }

        return true;
    }

    unsigned int getLongestChain() const {
        if (m_longestChain == 0) {
            processDefferedWords();
        }

        return m_longestChain;
    }

private:
    unsigned int m_accessMatrix[26][26];
    unsigned int m_defferedWords[26][26];
    unsigned int m_totalIncome[26];
    unsigned int m_defferedCount;
    unsigned int m_longestChain;

    void processDefferedWords() {
        unsigned int starting_from = 0;
        unsigned int from = 0;
        unsigned int starting_to = 0;
        unsigned int to = 0;

        // add words that are poiting to itself
        for (unsigned int i=0; i < 26; i++) {
            m_accessMatrix[i][i] = m_defferedWords[i][i];
            if (m_longestChain < m_accessMatrix[i][i]) {
                m_longestChain = m_accessMatrix[i][i];
            }
            m_defferedCount -= m_defferedWords[i][i];
            m_defferedWords[i][i] = 0;
        }

        while (m_defferedCount != 0) {
            for (; starting_from < 26; starting_from++) {
                for (;starting_to < 26; starting_to++) {
                    if (m_defferedWords[from][to] != 0) {
                        break;
                    }
                }
            }

            from = starting_from;
            to = starting_to;

            if (m_totalIncome[from] + 1 < m_defferedWords[from][to]) {
                unsigned int max = m_totalIncome[from] + 1;
                unsigned int diff = m_defferedWords[from][to] - max;

                m_defferedCount -= diff;
                m_totalIncome[to] -= diff;
                m_defferedWords[from][to] = max;
            }

            do {
                add_connection(from, to);
                from = to;
            } while ( get_next_to(from, to));
        }
    }

    void add_connection(unsigned int from, unsigned int to) {
        m_totalIncome[to]--;
        m_defferedCount--;
        m_defferedWords[from][to]--;

        // do magic
    }

    bool get_next_to( unsigned int from, unsigned int &to) {
        for (unsigned int i=0; i < 26; i++) {
            if (m_defferedWords[from][i] != 0) {
                to = i;
                return true;
            }
        }

        return false;
    }
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
    unique_ptr<WordChain> wc( new WordChain);
    size_t start = 0;

    while ( wc->addWord( getWord(line, start) ) ) {}

    unsigned int length = wc->getLongestChain();
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
