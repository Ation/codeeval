#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

typedef int (*functor)(int, int);

int add_functor(int left, int right) {
    return left + right;
}

int mult_functor(int left, int right) {
    return left * right;
}

int div_functor(int left, int right) {
    return left / right;
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
        stack<functor> operators;
        queue<int> numbers;

        int i;
        char current;

        for (i=0; i<inputLine.length(); i++) {
            current = inputLine[i];
            if (current == ' ') {
                continue;
            }

            switch (current) {
            case '+':
                operators.push(add_functor);
                continue;
            case '*':
                operators.push(mult_functor);
                continue;
            case '/':
                operators.push(div_functor);
                continue;
            }

            // current should be a number
            break;
        }

        // enter the numbers
        for (; i < inputLine.length(); i++) {
            int v=0;

            for (; i < inputLine.length(); i++) {
                current = inputLine[i];
                if (current == ' ') {
                    break;
                }

                v += v * 10 + (current - '0');
            }

            numbers.push(v);
        }

        functor _f;
        int right;
        int left = numbers.front();
        numbers.pop();

        while (!operators.empty()) {
            right = numbers.front();
            numbers.pop();

            _f = operators.top();
            operators.pop();

            left = _f(left, right);
        }

        cout << left << endl;
    }

    return 0;
}
