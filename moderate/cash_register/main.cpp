#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class Printer {
private:
    typedef void (Printer::*printerFunction)(const string &value);

public:
    Printer() : m_printer(&Printer::firstPrinter) {
    }

    void print(const string &value) {
        (this->*m_printer)(value);
    }
private:
    printerFunction m_printer;

    void firstPrinter(const string &value) {
        m_printer = &Printer::nextPrinter;
        // print
        cout << value;
    }

    void nextPrinter(const string &value) {
        // print
        cout << ',' << value ;
    }
};

vector < pair < string, unsigned int > > cash =
{
    { "PENNY", 01} ,
    { "NICKEL", 05} ,
    { "DIME", 10} ,
    { "QUARTER", 25} ,
    { "HALF DOLLAR", 50} ,
    { "ONE", 100} ,
    { "TWO", 200} ,
    { "FIVE", 500} ,
    { "TEN", 1000} ,
    { "TWENTY", 2000} ,
    { "FIFTY", 5000} ,
    { "ONE HUNDRED", 10000}
};

unsigned int getPrice(const string& line, size_t &position) {
    unsigned int multiplier = 100;
    unsigned int result = 0;

    for (; position < line.length(); position++) {
        if (line[position] == '.') {
            position++;

            for (unsigned int i=0; i < 2; i++, position++) {

                multiplier /= 10;
                result = result * 10 + (line[position] - '0');
            }

            position ++;

            break;
        }
        if (line[position] == ';') {
            position++;
            break;
        }

        result = result * 10 + (line[position] - '0');
    }

    if (multiplier) {
        result *= multiplier;
    }

    return result;
}

void printCash(const string &line) {
    size_t position = 0;
    unsigned int price;
    unsigned int amount;

    Printer cashier;

    price = getPrice(line, position);
    amount = getPrice(line, position);

    if (price == amount) {
        cout << "ZERO" << endl;
        return;
    }

    if (price > amount) {
        cout << "ERROR" << endl;
        return;
    }

    amount -= price;

    for (auto i = cash.rbegin(); i != cash.rend() && amount != 0; ++i) {
        while (amount >= i->second) {
            cashier.print(i->first);
            amount -= i->second;
        }
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
        printCash(inputLine);
    }

    return 0;
}
