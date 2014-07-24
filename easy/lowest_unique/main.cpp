#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void printLowestUnique(const string &line) {
    int counter[10];
    int players[10];

    memset(counter, 0, sizeof(int) * 10);
    memset(players, 0, sizeof(int) * 10);

    counter[9] = 1;
    players[9] = 0;

    int player_id = 1;
    int number;

    for (size_t position = 0; position < line.length(); position += 2, player_id++) {
        number = line[position] - '0' -1;
        counter[ number ]++;
        players[number ] = player_id;
    }

    int winnerId = 0;
    for (int i=0; i < 10; i++) {
        if (counter[i] == 1) {
            winnerId = players[i];
            break;
        }
    }

    cout << winnerId << endl;
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
        printLowestUnique(inputLine);
    }

    return 0;
}
