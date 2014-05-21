#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

typedef double (*functor)(double, double);

double add_functor(double left, double right) {
    return left + right;
}

double mult_functor(double left, double right) {
    return left * right;
}

double div_functor(double left, double right) {
    return left / right;
}

int getInteger(const string &line, size_t &position) {
    int result = 0;
    char temp;

    for (; position < line.length(); position++) {
        temp = line[position];

        if (temp == ' ') {
            position++;
            break;
        }

        result = result * 10 + (temp - '0');
    }

    return result;
}

int calculateExpression(const string &line) {
    stack<functor> operators;

    functor     f;

    size_t position = 0;
    char    temp;
    for (; position < line.length(); position += 2) {
        temp = line[position];
        if (temp >= '0' && temp <= '9') {
            break;
        }

        switch (temp) {
        case '+':
            operators.push(add_functor);
            break;
        case '*':
            operators.push(mult_functor);
            break;
        case '/':
            operators.push(div_functor);
            break;
        default:
            break;
        }
    }

    double left = getInteger(line, position);
    int right;
    while (!operators.empty()) {
        f = operators.top();
        operators.pop();

        right = getInteger(line, position);

        left = f(left, right);
    }

    return left;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    bool end_line = false;
    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        if (end_line) {
            cout << endl;
        }
        cout << calculateExpression(inputLine);
        end_line = true;
    }

    return 0;
}
