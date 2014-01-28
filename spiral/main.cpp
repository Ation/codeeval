#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef void (*print_function)(const string& );

static print_function printer;

void space_print(const string&  _s) {
    cout << " " << _s;
}

void just_print(const string&  _s) {
    cout << _s;
    printer = space_print;
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

    vector<string>    symbols;

    while ( getline(inFile, inputLine)) {
        if (inputLine.length() < 5) {
            break;
        }

        printer = just_print;
        int x_size = 0;
        int y_size = 0;

        int total_size;
        int end;

        int top_offset = 0;
        int bottom_offset = 0;
        int left_offset = 0;
        int right_offset = 0;

        int input_iterator = 0;
        while (';' != inputLine[input_iterator]) {
            y_size = y_size*10 + (inputLine[input_iterator] - '0');
            ++input_iterator;
        }

        ++input_iterator;
        while (';' != inputLine[input_iterator]) {
            x_size = x_size*10 + (inputLine[input_iterator] - '0');
            ++input_iterator;
        }
        ++input_iterator;

        int i=0;
        total_size = x_size * y_size;
        symbols.resize(total_size);
        // get the symbols
        while (inputLine.size() != input_iterator) {
            if (' ' != inputLine[input_iterator]) {
                int begin = input_iterator;
                while ( input_iterator != inputLine.size() && inputLine[input_iterator] != ' ') input_iterator++;

                symbols[i] = (inputLine.substr(begin, input_iterator-begin));
                i++;
                if (i == total_size) {
                    break;
                }
            } else {
                ++input_iterator;
            }
        }

        if (i != total_size) {
            break;
        }

        top_offset = 0;
        left_offset = 0;

        i =0;
        end = 0;

        int x;
        int y;
        // so we do have plain array
        while (true) {
            // right
            for (x=left_offset, y = top_offset; x < x_size - right_offset; x++) {
                printer(symbols[y*x_size + x]);
            }
            top_offset++;
            if (top_offset + bottom_offset == y_size) {
                break;
            }

            //down
            for (x--, y=top_offset; y < y_size - bottom_offset; y++) {
                printer(symbols[y*x_size + x]);
            }
            right_offset++;
            if (right_offset + left_offset == x_size) {
                break;
            }

            // left
            for (y--, x--; x >= left_offset; x--) {
                printer(symbols[y*x_size + x]);
            }
            bottom_offset++;
            if (top_offset + bottom_offset == y_size) {
                break;
            }

            // up
            for (x++, y--; y >= top_offset; y--) {
                printer(symbols[y*x_size + x]);
            }
            left_offset++;
            if (right_offset + left_offset == x_size) {
                break;
            }
        }
        cout << endl;
    }

    return 0;
}
