#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class MineSweeper
{
private:
    char    **m_matrix;

    size_t  m_rows;
    size_t  m_columns;

    size_t  m_taskRows;
    size_t  m_taskColumns;

public:
    MineSweeper() {
        allocateField(9, 9);
    }

    void initMatrix(const string &line) {
        size_t position = 0;
        size_t  rows = getInteger(line, position);
        size_t  columns = getInteger(line, position);

        reallocateField(rows, columns);

        for (size_t i=0; i < rows; i++) {
            for (size_t j=0; j < columns; j++) {
                if (line[position] == '*') {
                    m_matrix[i][j] = '*';

                    int starting_i = i-1;
                    int starting_j = j-1;

                    int ending_i = i + 1;
                    int ending_j = j + 1;

                    if (starting_i < 0) {
                        starting_i = 0;
                    }

                    if (starting_j < 0) {
                        starting_j = 0;
                    }

                    if (ending_i == m_taskRows) {
                        ending_i--;
                    }

                    if (ending_j == m_taskColumns) {
                        ending_j--;
                    }

                    for (int __i = starting_i; __i <= ending_i; __i++) {
                        for (int __j = starting_j; __j <= ending_j; __j++) {
                            if (m_matrix[__i][__j] != '*') {
                                m_matrix[__i][__j]++;
                            }
                        }
                    }
                }

                position++;
            }
        }
    }

    void printField() const {
        for (size_t i = 0; i< m_taskRows; i++) {
            cout << m_matrix[i];
        }

        cout << endl;
    }
private:
    int getInteger(const string &line, size_t &position) {
        int result = 0;

        char symbol;
        while (position < line.length()) {
            symbol = line[position];

            if (symbol >= '0' && symbol <= '9') {
                result = result * 10 + (symbol - '0');
                position++;
            } else {
                position++;
                break;
            }
        }

        return result;
    }

    void reallocateField(size_t rows, size_t columns) {
        if ((rows > m_rows) || (columns > m_columns)) {
            freeMatrix();
            allocateField(rows, columns );
        }

        m_taskRows = rows;
        m_taskColumns = columns;

        for (size_t i=0; i < m_taskRows; i++) {
            for (size_t j=0; j < m_taskColumns; j++) {
                m_matrix[i][j] = '0';
            }
            m_matrix[i][m_taskColumns] = 0;
        }
    }

    void allocateField(size_t rows, size_t columns) {
        m_rows = rows;
        m_columns = columns;
        m_matrix = (char**)malloc(rows * sizeof(char*));

        for (size_t i=0; i < rows; i ++) {
            m_matrix[i] = (char*)malloc(sizeof(char) * (columns + 1));
            m_matrix[i][columns] = 0;
        }
    }

    void freeMatrix() {
        for (size_t i=0; i < m_rows; i++) {
            free(m_matrix[i]);
        }

        free(m_matrix);
    }

};

int main(int argc, char *argv[]) {
    MineSweeper sweeper;

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        sweeper.initMatrix(inputLine);
        sweeper.printField();
    }

    return 0;
}
