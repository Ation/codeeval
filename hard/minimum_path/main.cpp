#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class PathFinder{
private:
    int     **m_path;
    int     **m_matrix;

    size_t  m_size;
    size_t  m_taskSize;

    size_t  m_initRow;

    void allocateMatrix(size_t size) {
        m_size = size;

        m_path = (int**)malloc(size * sizeof(int*));
        m_matrix = (int**)malloc(size * sizeof(int*));

        for (size_t i=0; i < m_size; i++) {
            m_path[i] = (int*)malloc(m_size * sizeof(int));
            m_matrix[i] = (int*)malloc(m_size * sizeof(int));
        }
    }

    void free_matrix() {
        for (size_t i=0; i < m_size; i++) {
            free((void*)m_path[i]);
            free((void*)m_matrix[i]);
        }

        free(m_path);
        free(m_matrix);
    }

public:
    PathFinder() {
        allocateMatrix(10);
    }

    void initTo(const string &line) {
        size_t position = 0;
        int new_size = getInteger(line, position);

        if (m_size < new_size) {
            free_matrix();
            allocateMatrix(new_size);
        }

        m_taskSize = new_size;
        m_initRow = 0;

        for (size_t i = 0; i < m_taskSize; i++) {
            for (size_t j = 0; j < m_taskSize; j++) {
                m_path[i][j] = -1;
            }
        }
    }

    void addRow(const string &line) {
        int value;
        size_t position = 0;

        for (size_t j = 0; j < m_taskSize; j++) {
            value = getInteger(line, position);
            m_matrix[m_initRow][j] = value;
        }
        m_initRow++;
    }

    bool    isInitialized() const {
        return m_initRow == m_taskSize;
    }

    int getPath() {
        m_path[0][0] = m_matrix[0][0];

        int current;
        int next;
        int existing;

        for (size_t i=0; i < m_taskSize; i++) {
            for (size_t j = 0; j < m_taskSize; j++) {
                current = m_path[i][j];

                //down
                if (i != m_taskSize - 1) {
                    next = current + m_matrix[i+1][j];
                    existing = m_path[i+1][j];
                    if ((existing == -1) || (existing > next)) {
                        m_path[i+1][j] = next;
                    }
                }

                // right
                if (j != m_taskSize - 1) {
                    next = current + m_matrix[i][j+1];
                    existing = m_path[i][j+1];
                    if ((existing == -1) || (existing > next)) {
                        m_path[i][j+1] = next;
                    }
                }
            }
        }

        return m_path[m_taskSize - 1][m_taskSize - 1];
    }
private:
    int getInteger(const string &line, size_t &position) {
        int result = 0;

        char symbol;
        for (; position < line.length(); position++) {
            symbol = line[position];
            if (symbol >= '0' && symbol <= '9') {
                result = result * 10 + (symbol - '0');
            } else {
                position++;
                break;
            }
        }

        return result;
    }

    bool    canMoveDown(size_t i) const {
        return i < m_taskSize;
    }

    bool    canMoveRight(size_t j) const {
        return j < m_taskSize;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    PathFinder  finder;

    while ( getline(inFile, inputLine)) {
        finder.initTo(inputLine);

        while (!finder.isInitialized()) {
            getline(inFile, inputLine);
            finder.addRow(inputLine);
        }

        cout << finder.getPath() << endl;
    }

    return 0;
}
