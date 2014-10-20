#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool get_code(const string &message, size_t &position, unsigned int &offset) {
    offset = 0;

    if (position + 2 > message.length()) {
        return false;
    }

    if (message[position] == ' ') {
        cout << ' ';
        position++;
        if (position + 2 >= message.length()) {
            return false;
        }
    }

    offset = message[position] - '0';
    offset *= 10;
    offset += message[position + 1] - '0';

    position += 2;

    return true;
}

void print_by_offset(const string &message, const string &key_alpha) {
    size_t position = 0;
    unsigned int current_offset = 0;
    unsigned int offset = 0;

    while ( get_code(message, position, offset) ) {
        current_offset = offset;

        cout << key_alpha[current_offset];
    }
    cout << endl;
}

void print_diff_codes(const string &key, const string &orig) {
    for (int i=0; i < key.length(); i++) {
        cout << key[i] << ' ' << orig[i] << ' ' << ((int)( key[i] - orig[i] ) + i) << endl;
    }
}

void decode_diff_count(const string &message, const string &key, const string &alpha) {
    vector<char> decoder;
    size_t position = 0;

    decoder.resize(key.length(), 0);

    unsigned int code;
    for (int i=0; i < key.length(); i++) {
        code = (unsigned int)( key[i] - alpha[i] ) + i;
        decoder[code] = alpha[i];
    }

    while ( get_code(message, position, code) ) {
        cout << decoder[code];
    }
}

int main(int argc, char *argv[]) {
    const string key_alpha = "BHISOECRTMGWYVALUZDNFJKPQX";
    const string alpha     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //ALL PEERS START SEEDING AT MIDNIGHT KTHXBAI
    const string message = "012222 1114142503 0313012513 03141418192102 0113 2419182119021713 06131715070119";
    decode_diff_count(message, key_alpha, alpha);

    return 0;
}
