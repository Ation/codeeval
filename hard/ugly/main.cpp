#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool    isUgly(int number) {
    return ( ( number % 2 == 0) ||
             ( number % 3 == 0) ||
             ( number % 5 == 0) ||
             ( number % 7 == 0));
}

int plusFunctor(int left, int right) {
    return left + right;
}

int minusFunctor(int left, int right) {
    return left - right;
}

typedef int (*functorPointer)(int, int);

class UglyValuator {
public:
    UglyValuator(int *numbers, int length) : m_numbers(numbers), m_length(length), m_result(0) {}
    ~UglyValuator() {}

    int valuate() {
        valuateUgly(0, 0, plusFunctor);

        return m_result;
    }

private:
    int     *m_numbers;
    unsigned int     m_length;
    int     m_result;

    void valuateUgly(int left, unsigned int index, functorPointer functor) {
        int current = m_numbers[index];
        int join = current;

        if (index == 0) {
            index = 1;

            valuateUgly(current, index, plusFunctor);
            valuateUgly(current, index, minusFunctor);

            for (; index < m_length - 1; ++index) {
                join = join * 10 + m_numbers[index];

                valuateUgly(join, index + 1, plusFunctor);
                valuateUgly(join, index + 1, minusFunctor);
            }

			join = join*10 + m_numbers[index];
			if (isUgly(join)) {
				++m_result;
			}
        } else {
            int currentLeft = functor(left, current);
            ++index;

			if (index == m_length) {
				if (isUgly(currentLeft)) {
					m_result++;
				}
			} else {
				valuateUgly(currentLeft, index, plusFunctor);
				valuateUgly(currentLeft, index, minusFunctor);
			

				for (; index < m_length - 1; ++index) {
					join = join * 10 + m_numbers[index];
					currentLeft = functor(left, join);

					valuateUgly(currentLeft, index + 1, plusFunctor);
					valuateUgly(currentLeft, index + 1, minusFunctor);
				}

				join = join * 10 + m_numbers[index];
				if (isUgly(functor(left, join))) {
					++m_result;
				}
			}
        }
    }
};

int     getUglyCount(const string& inString) {
    int result = 0;

    const unsigned int length = inString.length();
    int *numbers = new int[length];

    for (unsigned int i=0; i < length; ++i) {
        numbers[i] = inString[i] - '0';
    }

    if ( length == 1) {
        if (isUgly(numbers[0])) {
            result = 1;
        }
    } else {
        UglyValuator valuator(numbers, length);

        result = valuator.valuate();
    }

    delete numbers;

    return result;
}

int main(int argc, char *argv[]) {
    if ( 2 != argc ) {
        return 1;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        cout << getUglyCount(inputLine) << endl;
    }

    return 0;
}
