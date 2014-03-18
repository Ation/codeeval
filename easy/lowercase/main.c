#include <stdio.h>

#define LINE_SIZE 100

int main(int argc, char *argv[]) {
	FILE *_f;
    char line[LINE_SIZE];
    int position = 0;
    char c;
    if (argc != 2) {
        return 0;
    }

    _f = fopen(argv[1], "r");
    if (_f == NULL) {
        return 1;
    }

    while (fgets(line, LINE_SIZE, _f) != NULL) {
        for (position = 0; line[position] != 0; position++) {
            c = line[position];
            if (c >= 'A' && c <= 'Z') {
                line[position] = c + 32;
            }
        }

        printf(line);
    }

    return 0;
}
