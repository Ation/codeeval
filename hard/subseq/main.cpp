#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

class Sequence {
public:
    Sequence(int index, char symbol) : m_lastIndex(index) {
        m_sequence.reserve(10);
        m_sequence.push_back(symbol);
    }
    Sequence(const Sequence& src) : m_lastIndex(src.m_lastIndex), m_sequence(src.m_sequence) {}

    void    addSymbol(int lastIndex, char symbol) {
        m_lastIndex = lastIndex;
        m_sequence.push_back(symbol);
    }

    int     getLastIndex() const { return m_lastIndex; }
    int     length() const { return m_sequence.length(); }

    const string& getSequence() const { return m_sequence; }

	Sequence& operator = (const Sequence& src) {
		m_lastIndex = src.m_lastIndex;
		m_sequence = src.m_sequence;
		return *this;
	}
private:
    int     m_lastIndex;
    string  m_sequence;
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

    while ( getline(inFile, inputLine)) {
        if (inputLine.length() < 2) {
            continue;
        }

        // create index
        map<char, vector<int> > index;

        unsigned int i;
        for (i=0; inputLine[i] != ';'; ++i) {
            index[inputLine[i]].push_back(i);
        }
        ++i;
       
        char character;

        int latest_start_index = inputLine.length();
        list<Sequence> sequences;

        //seacrh for sequence
        for (; i < inputLine.length(); ++i) {
            character = inputLine[i];
            vector<int> &symbol_index = index[character];

            if ( ! symbol_index.empty()) {
                if (!sequences.empty()) {
                    list<Sequence>::iterator si;

                    for (si = sequences.begin(); si != sequences.end(); ++si) {
                        int last_index = (*si).getLastIndex();

                        vector<int>::iterator bound = lower_bound(symbol_index.begin(), symbol_index.end(), last_index + 1);
                        if (bound != symbol_index.end()) {
                            int bound_index = (*bound);
                            if (bound_index - last_index > 1) {
                                // create clone
                                sequences.insert(si, Sequence(*si));
                            }

                            (*si).addSymbol(bound_index, character);
                        }
                    }
                }

                int first_symbol_index = symbol_index[0];
                if (latest_start_index > first_symbol_index) {
                    sequences.push_front(Sequence(first_symbol_index, character));
                    latest_start_index = first_symbol_index;
                }
            }
        }

		list<Sequence>::iterator dsi = sequences.begin();
		Sequence longest(*dsi);

		dsi++;

        for (; dsi != sequences.end(); ++dsi) {
			if ((*dsi).length() > longest.length()) {
				longest = *dsi;
			}
        }

		cout << longest.getSequence() << endl;
    }

    return 0;
}
