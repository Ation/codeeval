#include <stdio.h>

#define LINE_SIZE 100

int main(int argc, char *argv[]) {
    FILE *_f;
    char line[LINE_SIZE + 1];
    size_t position = 0;
    size_t read;
    int number = 0;
    int sum = 0;
    char c;


    if (argc != 2) {
        return 0;
    }

    _f = fopen(argv[1], "r");
    if (_f == NULL) {
        return 1;
    }

    while ((read = fread(line, 1, LINE_SIZE, _f)) != 0) {
        for (position = 0; position < read; position++) {
            c = line[position];
            if (c >= '0' && c <= '9') {
                number = number * 10 + (c - '0');
            } else {
                sum += number;
                number = 0;
            }
        }
    }

    printf("%d", sum);

    return 0;
}
