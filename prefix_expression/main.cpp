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

    int left = getInteger(line, position);
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
// cout << calculateExpression("* 0 0") << endl; //0
// cout << calculateExpression("+ + + * + * / + / * / + * / / * + 4 2 9 6 4 7 5 1 3 7 9 6 0 2 1 5 0 8") << endl; //15
// cout << calculateExpression("+ / / * + / * + / * + + 0 6 8 5 1 4 3 3 9 0 4 1 2") << endl; //2
// cout << calculateExpression("* + * * + * / * * / / 6 7 8 7 9 6 8 0 7 4 1 4") << endl; //4
// cout << calculateExpression("/ + * * / / * / * + * + * / * / + 2 7 1 7 6 0 1 8 2 8 4 9 1 3 5 5 4 4") << endl; //376
// cout << calculateExpression("+ * + * + / / * * + / * / * * + * * * + * 3 5 4 2 4 3 8 5 1 2 9 3 0 5 8 2 8 7 4 7 9 7") << endl; //313522
// cout << calculateExpression("* / * + / / * 5 3 1 5 7 6 2 7") << endl; //210
// cout << calculateExpression("+ * / + + / * / * * / + / + / * / * / + * + / + * + * * 9 7 2 3 1 5 3 0 0 8 4 4 4 1 8 2 5 9 6 7 0 3 8 1 7 2 6 6 9") << endl; //15
// cout << calculateExpression("+ * / * * 4 6 4 9 0 7") << endl; //7
// cout << calculateExpression("/ * + 4 6 0 3") << endl; //0
// cout << calculateExpression("+ + * + / + + + + * * 1 3 6 4 1 7 0 2 3 4 7 5") << endl; //84
// cout << calculateExpression("+ * + / * / 0 8 4 9 3 5 8") << endl; //23
// cout << calculateExpression("* * * * 5 8 7 0 9") << endl; //0
// cout << calculateExpression("* + * 1 1 0 4") << endl; //4
// cout << calculateExpression("* / / * / * + / * * 6 8 2 6 5 7 3 0 8 4 7") << endl; //0
// cout << calculateExpression("+ * / * + + + * * * + / * / * * 7 9 1 5 7 3 6 4 9 4 8 2 8 8 2 5 6") << endl; //98286
// cout << calculateExpression("/ + * 6 4 0 3") << endl; //8
// cout << calculateExpression("+ * * * / * + * + / / * * * * * * + + + * + / 3 1 0 9 8 7 6 3 3 0 0 7 8 6 2 5 7 5 5 9 1 9 8 1") << endl; //1585
// cout << calculateExpression("/ * / * + / * * / / * + * * / + / / * * + * / + 0 8 5 1 7 9 5 1 7 4 6 3 0 8 7 9 2 0 8 9 2 6 3 5 4") << endl; //5
// cout << calculateExpression("+ / + 4 5 1 3") << endl; //12
// cout << calculateExpression("* * * / * * * + * / * + * / 4 1 0 5 1 6 3 0 4 4 7 7 6 1 7") << endl; //0
// cout << calculateExpression("+ + * * / 8 1 8 2 4 3") << endl; //135
// cout << calculateExpression("/ * * / + * + / 6 2 2 8 6 1 0 5 7") << endl; //0
// cout << calculateExpression("* + * + / + / / * 0 3 1 9 2 9 3 9 5 4") << endl; //128
// cout << calculateExpression("* + * 1 1 9 4") << endl; //40
// cout << calculateExpression("+ * + / * * + * / / * / * / * * / + + * / 5 1 7 1 4 6 8 5 9 6 7 2 2 1 8 3 0 3 3 0 8 7") << endl; //7
// cout << calculateExpression("/ * + / * + / 5 1 3 1 2 3 0 5") << endl; //0
// cout << calculateExpression("+ * / + / * * + / 7 5 4 4 1 7 3 3 0 2") << endl; //2
// cout << calculateExpression("/ 8 4") << endl; //2
// cout << calculateExpression("* / * * * + / + * + + * * * / * / / + / / * * 2 5 4 1 3 5 3 5 6 1 7 0 8 3 1 7 7 4 9 4 0 0 8 2") << endl; //0
// cout << calculateExpression("/ * + + * / 0 3 8 8 0 0 9") << endl; //0
// cout << calculateExpression("* * / * 4 0 2 2 8") << endl; //0
// cout << calculateExpression("/ / * / * * / * * / / * + * * / / / * * / 5 9 3 3 4 4 7 0 6 0 1 3 8 6 4 5 9 1 7 8 2 7") << endl; //0
// cout << calculateExpression("+ / 9 1 5") << endl; //14
// cout << calculateExpression("+ 0 3") << endl; //3
// cout << calculateExpression("* + / * + / * * + 5 3 7 7 6 4 0 8 4 9") << endl; //36
// cout << calculateExpression("* / * / * + + + * + * / * / * + 4 6 3 2 1 5 9 0 3 6 7 8 1 2 2 3 4") << endl; //136
// cout << calculateExpression("+ * * + * * / / + * * * / / + + / * * + 2 0 0 6 9 3 6 4 9 8 3 2 4 1 8 6 4 5 2 7 7") << endl; //77
// cout << calculateExpression("* + 2 3 4") << endl; //20
// cout << calculateExpression("+ * + + + + + * 2 3 8 0 6 0 4 6 7") << endl; //151

    if (argc != 2) {
        return 0;
    }

    string inputLine;
    ifstream inFile(argv[1]);

    if ( ! inFile.is_open() ) {
        return 1;
    }

    while ( getline(inFile, inputLine)) {
        cout << calculateExpression(inputLine) << endl;
    }

    return 0;
}
