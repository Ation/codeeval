#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <utility>
#include <algorithm>

using namespace std;


class Printer {
private:
    typedef void (Printer::*printerFunction)(int value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(int value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(int value) {
        cout.fill(' ');
        cout.width(0);

        m_printer = &Printer::nextPrinter;
        // print
        cout << value;
    }

    void nextPrinter(int value) {
        // print
        cout.fill('0');
        cout.width(4);
        cout << value;
    }
};

unsigned int getInteger(const string &line) {
    unsigned int result = 0;

    for (size_t i = 0 ; i < line.length(); ++i) {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}

class BigUInt {
public:
    BigUInt() {}

    explicit BigUInt(unsigned int value) {
        m_data.push_back(value);
    }

    BigUInt(const BigUInt& src) : m_data(src.m_data) {
    }

    BigUInt& operator = (const BigUInt &src) {
        m_data = src.m_data;

        return *this;
    }

    BigUInt& operator += (const BigUInt &right) {
        m_data.resize(right.m_data.size());

        for (unsigned int i=0; i < m_data.size(); ++i) {
            m_data[i] += right.m_data[i];
        }

        normalize();

        return *this;
    }

    friend BigUInt operator + (const BigUInt &left, const BigUInt &right) {
        BigUInt result;
        unsigned int i;

        if (left.m_data.size() > right.m_data.size()) {
            result.resize(left.m_data.size());

            for (i=0; i < right.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i] + right.m_data[i];
            }

            for (; i< left.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i];
            }

        } else {
            result.resize(right.m_data.size());

            for (i=0; i < left.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i] + right.m_data[i];
            }

            for (; i< right.m_data.size(); ++i) {
                result.m_data[i] = right.m_data[i];
            }
        }

        result.normalize();

        return result;
    }

    friend BigUInt operator - (const BigUInt &left, const BigUInt &right) {
        BigUInt result;
        unsigned int i;

        if (left.m_data.size() > right.m_data.size()) {
            result.resize(left.m_data.size());

            for (i=0; i < right.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i] - right.m_data[i];
            }

            for (; i< left.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i];
            }

        } else {
            result.resize(right.m_data.size());

            for (i=0; i < left.m_data.size(); ++i) {
                result.m_data[i] = left.m_data[i] - right.m_data[i];
            }

            for (; i< right.m_data.size(); ++i) {
                result.m_data[i] = right.m_data[i];
            }
        }

        result.neg_normalize();

        return result;
    }

    friend BigUInt operator * (const BigUInt &left, const BigUInt &right) {
        if (left.m_data.size() < right.m_data.size()) {
            return right * left;
        }

        vector< BigUInt > accumulator;

        accumulator.reserve(right.m_data.size());

        for (unsigned int i=0; i < right.m_data.size(); i++) {
            accumulator.emplace_back( move( multOffset(left, right.m_data[i], i) ) );
        }

        BigUInt result;

        for (auto it = accumulator.begin(); it != accumulator.end(); ++it) {
            result += *it;
        }

        return result;
    }

    friend BigUInt operator * (const BigUInt &left, unsigned int right) {
        BigUInt result(left);

        for (unsigned int i=0; i < result.m_data.size(); ++i) {
            result.m_data[i] *= right;
        }

        result.normalize();

        return result;
    }

    void print() const {
        Printer p;

        for (auto it = m_data.rbegin(); it != m_data.rend(); ++it) {
            p.print(*it);
        }
        cout << endl;
    }

    BigUInt minus(const BigUInt &other) const {
        return BigUInt();
    }
private:
    void resize(unsigned int size) {
        m_data.resize(size);
    }

    static BigUInt multOffset(const BigUInt &left, int value, int offset) {
        BigUInt result;

        result.resize(offset + left.m_data.size());
        for (unsigned int i=0; i < left.m_data.size(); ++i) {
            result.m_data[i+offset] = left.m_data[i] * value;
        }

        result.normalize();

        return result;
    }

    void normalize() {
        int left = 0;
        for (unsigned int i = 0; i < m_data.size(); ++i)
        {
            if (left) {
                m_data[i] += left;
            }

            if (m_data[i] >= Limit) {
                left = m_data[i] / Limit;
                m_data[i] %= Limit;
            } else {
                left = 0;
            }
        }
        if (left != 0) {
            m_data.push_back(left);
        }
    }

    void neg_normalize() {
        int left = 0;
        for (unsigned int i = 0; i < m_data.size(); ++i)
        {
            if (left) {
                m_data[i] -= left;
            }

            if (m_data[i] < 0) {
                left = 1;
                m_data[i] += Limit;
            } else {
                left = 0;
            }
        }
    }

    vector<int>     m_data;
    const int Limit = 10000;
};

template< class T>
pair< T, T> getFibMult(unsigned int index) {
    if (index == 0) {
        return pair< T, T>(T(0), T(1));
    } else {
        auto fibs = getFibMult<T>(index >> 1);

        auto c = fibs.first * (fibs.second * 2 - fibs.first);
        auto d = fibs.second * fibs.second + fibs.first * fibs.first;

        if (index % 2 == 0) {
            return pair< T, T>(c, d);
        } else {
            return pair< T, T>(d, c + d);
        }
    }
}

template< class T>
T getBigFibonacci(unsigned int index) {
    auto result = getFibMult<T>(index);
	return result.first;
}

void printCombinations(const string &line) {
    unsigned int stairs_cout = getInteger(line);

    if (stairs_cout <= 92) {
        cout << getBigFibonacci<unsigned long long>(stairs_cout + 1) << endl;
    } else {
        getBigFibonacci<BigUInt>(stairs_cout + 1).print();
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
        printCombinations(inputLine);
    }

    return 0;
}
