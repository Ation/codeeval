#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

static unsigned int get_sum_to(unsigned int to) {
    return ( to < 2 ? to : ( to * (to + 1)) >> 1);
}

static unsigned int get_count_10x10(unsigned int index) {
    return (index < 2 ? 100 : 100 - get_sum_to(index - 1));
}

class Counter {
public:
    Counter() : m_total(0) {}

    bool count_100x1000(unsigned int index) {
        if (index > 2) {
            return false;
        }

        unsigned int total = 0;

        for (unsigned int square_index = 0; square_index + index < 12; square_index++ ) {
            unsigned int square_total = get_count_10x10(square_index + index);
            if (square_index < 10) {
                total += square_total * (square_index + 1);
            } else {
                total += square_total * ( 9 - (square_index - 10));
            }
        }

        m_total += total * (index + 1);

        return true;
    }

    unsigned int getTotal() const {
        return m_total;
    }
private:
    unsigned int m_total;
};

int main(int argc, char *argv[]) {
    Counter counter;

    unsigned int index = 0;
    while (counter.count_100x1000(index)) {
        index++;
    }

    unsigned int positive_total = counter.getTotal();

    positive_total -= 1;

    unsigned int doubled = 298 * 2;
    positive_total -= doubled;

    cout << ( (positive_total << 2) + (doubled << 1) + 1) << endl;

    return 0;
}
