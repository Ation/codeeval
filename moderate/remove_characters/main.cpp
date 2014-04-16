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

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    const int size = 'z' - 'a' + 1;
    char clear[size];
    size_t out_length = 30;
    char *out_string;

    out_string = (char*)malloc(out_length);

    while ( getline(inFile, inputLine)) {
        memset(clear, 0, size);
        const char* data = inputLine.c_str();

        size_t  coma_position = 0;
        size_t  i, j;

        for (i=0; i < inputLine.length(); i++) {
            if (data[i] == ',') {
                coma_position = i;
                break;
            }
        }

        for (; i < inputLine.length(); i++) {
            if (data[i] >= 'a' && data[i] <= 'z') {
                clear[data[i] - 'a'] = 1;
            }
        }

        if (coma_position > out_length) {
            free(out_string);
            out_length = coma_position + 10;
            out_string = (char*)malloc(out_length);
        }

        for (i=0, j=0; i < coma_position; i++) {
            if ( data[i] < 'a' || data[i] > 'z' || !clear[ data[i] - 'a']) {
                out_string[j] = data[i];
                j++;
            }
        }

        out_string[j] = 0;

        cout << out_string << endl;
    }

    return 0;
}
