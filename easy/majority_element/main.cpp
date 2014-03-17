#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void findMajorVote(const string &line, int *freqMatrix)
{
    int major = -1;
    int count = 0;
    int current;

    int totalCount = 0;
    int lineIndex = 0;

    memset(freqMatrix, 0, 101*sizeof(int));

    current = 0;

    for (; lineIndex < line.length(); ++lineIndex) {
        if (line[lineIndex] == ',') {
            lineIndex++;
            break;
        }
        current = current * 10 + (line[lineIndex] - '0');
    }

    count = totalCount = 1;
    major = current;
    freqMatrix[current]++;

    while ( lineIndex < line.length() ) {
        // get number
        current = 0;
        for (; lineIndex < line.length(); ++lineIndex) {
            if (line[lineIndex] == ',') {
                lineIndex++;
                totalCount++;
                break;
            }
            current = current * 10 + (line[lineIndex] - '0');
        }

        freqMatrix[current]++;
        if (current == major) {
            count ++;
        } else {
            count --;
        }

        if (count == 0) {
            count = 1;
            major = current;
        }
    }

    if (freqMatrix[major] > (totalCount / 2) ) {
        cout << major << endl;
    } else {
        cout << "None" << endl;
    }
}

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

    while ( getline(inFile, inputLine)) {
        findMajorVote(inputLine, fM);
    }

    return 0;
}
