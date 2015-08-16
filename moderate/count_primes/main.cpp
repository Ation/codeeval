#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

unsigned int getUnsignedInteger(const string &line, size_t &position) {
    unsigned int result = 0;
    char temp;
    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    return result;
}

static vector<unsigned int> primes{2,3,5,7,11,13,17,19};

bool is_prime(unsigned int number) {
    for (auto p : primes) {
        if ((number % p) == 0) {
            return false;
        }
    }

    return true;
}

unsigned int count_primes(const string &line) {
    size_t position = 0;

    unsigned int lower = getUnsignedInteger(line, position);
    unsigned int upper = getUnsignedInteger(line, position);

    if (upper > primes.back()) {
        unsigned int last = primes.back() + 2;
        while (last <= upper) {
            if (is_prime(last)) {
                primes.push_back(last);
            }
            last += 2;
        }
    }

    auto lower_it = lower_bound(primes.begin(), primes.end(), lower);
    auto upper_it = upper_bound(lower_it, primes.end(), upper);

    return distance(lower_it, upper_it);
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
        cout << count_primes(inputLine) << endl;
    }

    return 0;
}
