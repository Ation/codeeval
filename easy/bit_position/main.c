#include <stdio.h>

#define LINE_SIZE 100

int getNumber(char *buffer, int *position, FILE *file, int *number) {
    int result = 0;

    while (1) {
        if (buffer[*position] >= '0' && buffer[*position] <= '9') {
            result = result * 10 + (buffer[*position] - '0');
            (*position)++;
            continue;
        }

        if (buffer[*position] == 0) {
			if ( fgets(buffer, LINE_SIZE, file) == NULL) {
				if (feof(file)) {
					*position = -1;
				}
				*number = result;
				return 1;
			}

			*position = 0;
			continue;
        }

        // non digit character
        (*position)++;
        break;
    }

    *number = result;

    return 1;
}

int main(int argc, char *argv[]) {
	FILE *_f;
    char line[LINE_SIZE];
    int position = 0;

    int number;
    int b1;
    int b2;

    if (argc != 2) {
        return 0;
    }

    _f = fopen(argv[1], "r");
    if (_f == NULL) {
        return 1;
    }

    if (fgets(line, LINE_SIZE, _f) == NULL) {
        return 1;
    }

    while (position != -1) {
        if ( !getNumber(line, &position, _f, &number) ) {
            break;
        }
        if ( !getNumber(line, &position, _f, &b1) ) {
            break;
        }
        if ( !getNumber(line, &position, _f, &b2) ) {
            break;
        }

        if ( ( (number >> (b1 - 1)) & 1 ) == ((number >> (b2 - 1)) & 1 ) ) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    }

    return 0;
}
