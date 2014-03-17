#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    int *fM = (int*)malloc(101 * sizeof(int));

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    unsigned int i;
    unsigned int F;
    unsigned int B;
    unsigned int N;

    unsigned int current;

    while ( getline(inFile, inputLine)) {
        for (i=0, current = 0; inputLine[i] != ' '; i++) {
            current = current * 10 + (inputLine[i] - '0');
        }
        F = current;

        for (i = i+1, current = 0; inputLine[i] != ' '; i++) {
            current = current * 10 + (inputLine[i] - '0');
        }
        B = current;

        for (i = i+1, current = 0; i < inputLine.length(); i++) {
            current = current * 10 + (inputLine[i] - '0');
        }
        N = current;

        if (F == 1) {
            if (B == 1) {
                cout << 'FB';
            } else {
                cout << 'F';
            }
        } else {
            if (B == 1) {
                cout << 'B';
            } else {
                cout << 1;
            }
        }

        for ( i = 2; i <= N; i++) {
            if (i % F == 0) {
                if (i % B == 0) {
                    cout << " FB";
                } else {
                    cout << " F";
                }
            } else {
                if ( i % B == 0) {
                    cout << " B";
                } else {
                    cout << " " << i;
                }
            }
        }
        cout << endl;
    }

    return 0;
}
