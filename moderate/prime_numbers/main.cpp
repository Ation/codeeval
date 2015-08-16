#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

template< class _T >
class Printer {
private:
    typedef _T value_type;
    typedef void (Printer< value_type >::*printerFunction)(value_type value);

public:
    Printer() : m_printer(&Printer< value_type >::firstPrinter) {
    }

    void print(value_type value) {
        (this->*m_printer)( value );
    }
private:
    printerFunction m_printer;

    void firstPrinter(value_type value) {
        m_printer = &Printer< value_type >::nextPrinter;
        // print
        cout << value ;
    }

    void nextPrinter(value_type value) {
        // print
        cout << ',' << value;
    }
};

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

void print_primes(const string &line) {
    size_t position = 0;

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

    auto upper_it = lower_bound(primes.begin(), primes.end(), upper);

    Printer<unsigned int> p;

    for (auto i = primes.begin(); i < upper_it; ++i) {
        p.print(*i);
    }
    cout << endl;
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
        print_primes(inputLine);
    }

    return 0;
}
