#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unordered_map>

using namespace std;

static const unordered_map< string, int > digits_map = {{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
static const unordered_map< string, int > dozens_map = { { "ten", 10}, { "twenty", 20}, { "thirty", 30}, { "forty", 40}, { "fifty", 50}, { "sixty", 60}, { "seventy", 70}, { "eighty", 80}, { "ninety", 90} };

static const unordered_map< string, int > special_map = { { "eleven" , 11 }, { "twelve" , 12 }, { "thirteen" , 13 }, { "fourteen" , 14 }, { "fifteen" , 15 }, { "sixteen" , 16 }, { "seventeen" , 17 }, { "eighteen" , 18 }, { "nineteen" , 19 } };
static const unordered_map< string, int > multiplyers_map = { { "hundred", 100 }, { "thousand", 1000 }, { "million", 1000000 } };

static const string negative_word = "negative";

bool getWord(const string &line, size_t &position, string &word) {
    size_t start = position;
    size_t end;

    for (start = position; start < line.length(); start++) {
        if (line[start] != ' ') {
            break;
        }
    }

    if (start >= line.length()) {
        return false;
    }

    for (end = start; end < line.length(); end++) {
        if (line[end] == ' ') {
            end --;
            break;
        }
    }
    if (end >= line.length()) {
        end --;
    }

    word = line.substr(start, end - start + 1);

    position = end + 1;

    return true;
}

int getNumber(const string &line) {
    int result = 0;
    bool negative = false;
    string word;

    // state settings
    int current = 0;

    size_t position = 0;

    if (!getWord(line, position, word)) {
        return 0;
    }

    if (negative_word == word) {
        negative = true;
        if (!getWord(line, position, word)) {
            return 0;
        }
    }

    do {
        auto digit = digits_map.find(word);
        if (digit != digits_map.end()) {
            current += digit->second;
            continue;
        }

        auto special = special_map.find(word);
        if (special != special_map.end()) {
            current += special->second;
            continue;
        }

        auto dozen = dozens_map.find(word);
        if (dozen != dozens_map.end()) {
            current += dozen->second;
            continue;
        }

        auto mult = multiplyers_map.find(word);
        if (mult != multiplyers_map.end()) {
            current *= mult->second;
            if (mult->second != 100) {
                result += current;
                current = 0;
            }
            continue;
        }
    } while (getWord(line, position, word));

    result += current;

    if (negative) {
        result = -result;
    }

    return result;
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
        cout << getNumber(inputLine) << endl;
    }

    return 0;
}
