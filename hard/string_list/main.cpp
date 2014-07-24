#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

int getTestCaseLength(const string &line, size_t &position) {
    int result = 0;

    for (position = 0; position < line.length(); position++) {
        if (line[position] == ',') {
            position ++;
            break;
        }

        result = result * 10 + (line[position] - '0');
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

    vector<char>    symbols;
    vector<int>     indexes;

    set<char>       symbols_set;

    char            *result = nullptr;
    size_t          result_size = 0;


    while ( getline(inFile, inputLine)) {
        symbols_set.clear();

        size_t  stringStart;
        int length = getTestCaseLength(inputLine, stringStart);
        int last_index = length - 1;

        for (; stringStart < inputLine.length(); stringStart++) {
            symbols_set.insert(inputLine[stringStart]);
        }

        symbols.resize(symbols_set.size());
        indexes.resize(length);

        int i=0;
        for (auto si = symbols_set.begin(); si != symbols_set.end(); ++si) {
            symbols[i] = (*si);
            i++;
        }

        if (result_size < length + 1) {
            if (result != nullptr) {
                free(result);
            }

            result_size = length + 1;
            result = (char*)malloc(sizeof(char) * result_size);
        }

        for (i=0; i < length; i++) {
            indexes[i] = 0;
            result[i] = symbols[0];
        }

        result[i] = 0;

        cout << result;

        while (true) {
            for (i = last_index; i >= 0; i--) {
                indexes[i]++;
                if (indexes[i] == symbols.size()) {
                    indexes[i] = 0;
                    result[i] = symbols[0];
                } else {
                    result[i] = symbols[indexes[i]];
                    break;
                }
            }

            if (i == -1) {
                break;
            }

            cout << ',' << result;
        }

        cout << endl;
    }

    return 0;
}
