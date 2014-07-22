#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

bool isBalanced(const string &line) {
    int open_count = 0;
    int close_smile_count = 0;
    int open_smile_cout = 0;
    bool dots = false;

    for(auto&& c : line) {
        switch ( c ) {
        case ':':
            dots = true;
            break;
        case '(':
            if ( dots ) {
                dots = false;
                open_smile_cout++;
            } else {
                open_count++;
            }
            break;
        case ')':
            if (dots) {
                close_smile_count++;
                dots = false;
            } else {
                open_count--;
                if (open_count < 0) {
                    if (open_smile_cout == 0) {
                        return false;
                    }
                    open_smile_cout--;
                    open_count++;
                }
            }

            break;
        default:
            dots = false;
            break;
        }
    }

    if (open_count == 0) {
        return true;
    }

    if (open_count < 0) {
        return open_count + open_smile_cout >= 0;
    } else {
        return open_count - close_smile_count <= 0;
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
        cout << (isBalanced(inputLine) ? "YES" : "NO") << endl;
    }

    return 0;
}
