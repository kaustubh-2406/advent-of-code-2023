#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* consume_whitespace(char *ptr) {
    while (*ptr == ' ') {
        ptr += 1;
    }
    return ptr;
}

void print_int_list(int *list, int max) {
    for (int i = 0; i < max; i++) {
        printf("%d ", list[i]);
    }
}

char* parse_int_list(char *ptr, int *list) {
    ptr = consume_whitespace(ptr);
    
    int i = 0;
    while (*ptr != '|' && *ptr != '\n' && *ptr != '\0') {
        int num = strtol(ptr, &ptr, 10);
        list[i++] = num;
        ptr = consume_whitespace(ptr);
    }

    return ptr;
}

// constants
const int DRAWS = 25;
const int TOTAL = 250;
const int WIN_DRAWS = 10;
const int LINE_MAX = 200;

int main() {
    int sum_p1 = 0;
    int sum_p2 = 0;
    int line_num = 0;
    char line[LINE_MAX];

    int freq[TOTAL];
    for (int i = 0; i < TOTAL; i++) {
        freq[i] = 1;
    }

    while (fgets(line, LINE_MAX, stdin)) {
        bool isValid = true;
        char* endptr;
        long card = strtol(&line[5], &endptr, 10);

        // ignore ":"
        endptr += 1;

        int wins[WIN_DRAWS];
        int draws[DRAWS];
        for (int i = 0; i < WIN_DRAWS; i++) {
            wins[i] = 0;
        }
        for (int i = 0; i < DRAWS; i++) {
            draws[i] = 0;
        }
        while (*endptr != '\n' && *endptr != '\0') {
            endptr = parse_int_list(endptr, wins);

            // endptr = consume_whitespace(endptr);
            endptr += 1; // increment to account for '|'
            // endptr = consume_whitespace(endptr);

            endptr = parse_int_list(endptr, draws);

            // part 1....
            int count = 0;
            for (int i = 0; i < WIN_DRAWS && wins[i] != 0; i++) {
                for (int j = 0; j < DRAWS && draws[j] != 0; j++) {
                    if (wins[i] == draws[j]) {
                        count++;
                    }
                }
            }
            sum_p1 += pow(2, count - 1);

            // part 2...
            for (int i = 0; i < count && line_num + i + 1 < TOTAL; i++) {
                int indx = line_num + i + 1;
                freq[indx] += freq[line_num];
            }
            sum_p2 += freq[line_num];
        }
        
        line_num += 1;
    }


    printf("Part 1: %d, Part 2: %d\n", sum_p1, sum_p2);
    return 0;
}
