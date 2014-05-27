#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    char key[] = {'y','h','e','s','o','c','v','x','d','u','i','g','l','b','k','r','z','t','n','w','j','p','f','m','a','q'};
    char symbol;
    char *data;

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        data = const_cast<char*>(inputLine.c_str());
        for (size_t i=0; i < inputLine.length(); i++) {
            symbol = data[i];
            if (symbol != ' ') {
                data[i] = key[symbol-'a'];
            }
        }
        cout << data << endl;
    }

    return 0;
}
