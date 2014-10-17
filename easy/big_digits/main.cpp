#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

void printZero( vector<string> &output) {
    output[0].append("-**--");
    output[1].append("*--*-");
    output[2].append("*--*-");
    output[3].append("*--*-");
    output[4].append("-**--");
    output[5].append("-----");
}

void printOne( vector<string> &output) {
    output[0].append("--*--");
    output[1].append("-**--");
    output[2].append("--*--");
    output[3].append("--*--");
    output[4].append("-***-");
    output[5].append("-----");
}

void printTwo( vector<string> &output) {
    output[0].append("***--");
    output[1].append("---*-");
    output[2].append("-**--");
    output[3].append("*----");
    output[4].append("****-");
    output[5].append("-----");
}

void printThree( vector<string> &output) {
    output[0].append("***--");
    output[1].append("---*-");
    output[2].append("-**--");
    output[3].append("---*-");
    output[4].append("***--");
    output[5].append("-----");
}

void printFour( vector<string> &output) {
    output[0].append("-*---");
    output[1].append("*--*-");
    output[2].append("****-");
    output[3].append("---*-");
    output[4].append("---*-");
    output[5].append("-----");
}

void printFive( vector<string> &output) {
    output[0].append("****-");
    output[1].append("*----");
    output[2].append("***--");
    output[3].append("---*-");
    output[4].append("***--");
    output[5].append("-----");
}

void printSix( vector<string> &output) {
    output[0].append("-**--");
    output[1].append("*----");
    output[2].append("***--");
    output[3].append("*--*-");
    output[4].append("-**--");
    output[5].append("-----");
}

void printSeven( vector<string> &output) {
    output[0].append("****-");
    output[1].append("---*-");
    output[2].append("--*--");
    output[3].append("-*---");
    output[4].append("-*---");
    output[5].append("-----");
}

void printEight( vector<string> &output) {
    output[0].append("-**--");
    output[1].append("*--*-");
    output[2].append("-**--");
    output[3].append("*--*-");
    output[4].append("-**--");
    output[5].append("-----");
}

void printNine( vector<string> &output) {
    output[0].append("-**--");
    output[1].append("*--*-");
    output[2].append("-***-");
    output[3].append("---*-");
    output[4].append("-**--");
    output[5].append("-----");
}

void (*printers[])(vector<string>&) = {
    printZero,
    printOne,
    printTwo,
    printThree,
    printFour,
    printFive,
    printSix,
    printSeven,
    printEight,
    printNine};

void print_digits(const string &line) {
    vector<string> output;

    output.resize( 6 );
    size_t digits_count = 0;

    for( unsigned int i=0; i < line.length(); i++) {
        if ( isdigit(line[i]) ) {
            digits_count++;
        }
    }

    for(auto&& output_string : output) {
        output_string.reserve( digits_count * 5);
    }

    for( unsigned int i=0; i < line.length(); i++) {
        if ( isdigit(line[i]) ) {
            printers[ line[i] - '0'](output);
        }
    }

    for(auto&& output_string : output) {
        cout << output_string << endl;
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
        print_digits( inputLine );
    }

    return 0;
}
