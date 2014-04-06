#include <iostream>

using namespace std;

class LinePrinter {
public:
    LinePrinter() { 
        Reset();
    }
    ~LinePrinter() {}

    void Reset() {
        m_printer = &LinePrinter::startPrinter;
    }

    void Print(int value) {
        (this->*m_printer)(value);
    }
private:
    typedef void (LinePrinter::*printerFunction)(int);

    printerFunction m_printer;

    void startPrinter(int value) {
        cout << value ;

        m_printer = (value >= 10) ? &LinePrinter::printer100 : &LinePrinter::printer10;
    }

    void printer10(int value) {
        if (value >= 10) {
            m_printer = &LinePrinter::printer100;
            (this->*m_printer)(value);
        } else {
            cout << "   " << value;
        }
    }

    void printer100(int value) {
        if (value >= 100) {
            m_printer = &LinePrinter::printer1000;
            (this->*m_printer)(value);
        } else {
            cout << "  " << value;
        }
    }

    void printer1000(int value) {
        cout << " " << value;
    }
};

int main(int argc, char *argv[]) {
    LinePrinter printer;

    for (int i=1; i <= 12; i++) {
        printer.Reset();

        for (int j = i; j <= i * 12; j+= i) {
            printer.Print(j);
        }
        cout << endl;
    }

    return 0;
}