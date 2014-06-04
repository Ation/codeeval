#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stack>

using namespace std;

bool checkParentheses(const string &line) {
    stack<char> _s;
    char symbol;

    for (size_t i=0; i < line.length(); i++) {
        symbol = line[i];
        switch (symbol) {
        case '(':
        case '{':
        case '[':
            _s.push(symbol);
            break;
        case '}':
            if (_s.empty()) {
                return false;
            }
            if (_s.top() != '{') {
                return false;
            }
            _s.pop();
            break;
        case ']':
            if (_s.empty()) {
                return false;
            }
            if (_s.top() != '[') {
                return false;
            }
            _s.pop();
            break;
        case ')':
            if (_s.empty()) {
                return false;
            }
            if (_s.top() != '(') {
                return false;
            }
            _s.pop();
            break;
        }

        if (_s.size() > (line.length() >> 1) ) {
            return false;
        }
    }

    return _s.empty();
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
        cout << (checkParentheses(inputLine) ? "True" : "False") << endl;
    }

    return 0;
}
