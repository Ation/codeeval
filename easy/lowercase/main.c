#include <stdio.h>

#define LINE_SIZE 100

int main(int argc, char *argv[]) {
	FILE *_f;
    char line[LINE_SIZE + 1];
    size_t position = 0;
    size_t read;
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
            if (c >= 'A' && c <= 'Z') {
                line[position] = c + 32;
            }
        }

        line[position] = 0;
        printf("%s", line);
    }

    return 0;
}
