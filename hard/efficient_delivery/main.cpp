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

bool getUnsignedInteger(const string &line, size_t &position, unsigned int &number) {
    unsigned int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }
    }

    if (position >= line.length()) {
        return false;
    }

    for (; position < line.length(); position++) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            result = result * 10 + (temp - '0');
        } else {
            position ++;
            break;
        }
    }

    number = result;
    return true;
}

class DeliveryManager {
public:
    DeliveryManager() : m_volume(0), m_minAmount(0) {

    }

    void addTanker(unsigned int tanker) {
        m_tankers.push_back(tanker);
    }

    void setVolume(unsigned int volume) {
        m_volume = m_minAmount = volume;
    }

    void printDelivery() {
        vector<unsigned int> delivery_set;
        delivery_set.resize(m_tankers.size(), 0);

        loadTanker( delivery_set, m_tankers.size() - 1, m_minAmount);

        if (m_minAmount != 0) {
            cout << m_minAmount << endl;
        } else {
            sort(m_deliverySetVector.begin(), m_deliverySetVector.end(), deliverySetCompare);

            for(auto&& delivery_set : m_deliverySetVector) {
                printDeliverySet(delivery_set);
            }

            cout << endl;
        }
    }

private:
    static bool deliverySetCompare( const vector<unsigned int> &left, const vector<unsigned int> &right) {
        for (unsigned int i=0; i < left.size(); i++) {
            if (left[i] < right[i]) {
                return true;
            }
            if (left[i] > right[i]) {
                return false;
            }
        }

        return false;
    }

    vector<unsigned int> m_tankers;
    vector< vector < unsigned int > > m_deliverySetVector;
    unsigned int m_volume;
    unsigned int m_minAmount;

    void loadTanker( vector<unsigned int> &delivery_set, unsigned int tanker_level, unsigned int amount ) {
        unsigned int current_capacity = m_tankers[tanker_level];

        if (tanker_level != 0) {
            if (amount == 0) {
                delivery_set[tanker_level] = 0;
                loadTanker(delivery_set, tanker_level - 1, amount);
            } else {
                delivery_set[tanker_level] = amount / current_capacity;
                amount = amount % current_capacity;

                while (true) {
                    loadTanker(delivery_set, tanker_level - 1, amount);
                    if (delivery_set[tanker_level] == 0) {
                        break;
                    }

                    amount += current_capacity;
                    delivery_set[tanker_level]--;
                }
            }
        } else {
            // smaller one
            unsigned int to_add = amount % current_capacity;
            if (to_add == 0) {
                delivery_set[tanker_level] = amount / current_capacity;

                m_deliverySetVector.push_back(delivery_set);

                m_minAmount = 0;
            } else {
                to_add = current_capacity - to_add;
                if ( to_add < m_minAmount) {
                    m_minAmount = to_add;
                }
            }
        }
    }

    void printDeliverySet( const vector<unsigned int> &delivery_set) const {
        Printer<unsigned int> p;
        cout << '[' ;
        for (auto &&i = delivery_set.begin(); i != delivery_set.end(); ++i) {
            p.print(*i);
        }
        cout << ']';
    }
};

void printDelivery(const string &line) {
    DeliveryManager dm;

    size_t position = 0;

    unsigned int temp;
    unsigned int current;

    getUnsignedInteger(line, position, current);

    while (getUnsignedInteger( line, position, temp)) {
        dm.addTanker(current);
        current = temp;
    }

    dm.setVolume(current);

    dm.printDelivery();
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
        printDelivery(inputLine);
    }

    return 0;
}
