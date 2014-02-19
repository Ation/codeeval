#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

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
        stack<int>  values;
        int left;
        int right;
        char current;

        for (int i = inputLine.length()-1; i >= 0;/*do nothing*/) {
            current = inputLine[i];

            if (current >= '0' && current <= '9') {
                int next_value = 0;
                int m = 1;
                // read number and push on stack
                while ((i >= 0) && (current != ' ')) {
                    next_value += (current - '0') * m;
                    m *= 10;

                    --i;
                    current = inputLine[i];                    
                }

                do { --i; } while ((i >= 0) && (inputLine[i] == ' '));

                values.push(next_value);
            } else {
                left = values.top();
                values.pop();

                right= values.top();
                values.pop();

                switch (current) {
                case '+':
                    values.push(left + right);
                    break;
                case '*':
                    values.push(left*right);
                    break;
                case '/':
                    values.push(left/right);
                    break;
                default:
                    i = -1;
                    break;
                }

                do { --i; } while ((i >= 0) && (inputLine[i] == ' '));
            }
        }

        cout << values.top() << endl;
    }

    return 0;
}
