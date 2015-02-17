#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
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
        cout << ' ' << value;
    }
};

map<int, int> squares = {
    {   1 , 1} ,
    {   7 , 2} ,
    {  17 , 3} ,
    { 4*4*2 - 1 , 4} ,
    { 5*5*2 - 1 , 5} ,
    { 6*6*2 - 1 , 6} ,
    { 7*7*2 - 1 , 7} ,
    { 8*8*2 - 1 , 8} ,
    { 9*9*2 - 1 , 9} ,
    { 10*10*2 - 1 , 10}
};

class LineMatrix
{
public:
    explicit LineMatrix(const string &line) : _line( move(line)) {
        _size = get_size(_line);
    }

    char getElement(int x, int y) const {
        int offset = x*2 + _size*y*2;
        return _line[ offset ];
    }

    int size() {
        return _size;
    }


private:
    int _size;
    string _line;

    int get_size( const string &line ) {
        return squares[line.length() ];
    }
};


void rotate_matrix( const string &matrix_line ) {
    LineMatrix matrix( matrix_line);
    Printer<char> p;

    for( int x=0; x < matrix.size(); x++) {

        for (int y = matrix.size() - 1; y >= 0; y--) {
            p.print( matrix.getElement(x, y) );
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
        rotate_matrix( inputLine );
    }

    return 0;
}
