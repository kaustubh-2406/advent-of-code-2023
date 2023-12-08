#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// constants
const size_t LINE_MAX = 500;

char* consume_whitespace(char *ptr) {
    while (*ptr == ' ') {
        ptr += 1;
    }
    return ptr;
}

char* parse_list(char *ptr, size_t *list) {
    ptr = consume_whitespace(ptr);
    
    size_t i = 0;
    while (*ptr != '\n' && *ptr != '\0') {
        size_t num = strtol(ptr, &ptr, 10);
        list[i++] = num;
        ptr = consume_whitespace(ptr);
    }

    return ptr;
}

bool condition(size_t t, size_t time, size_t max_dist) {
    size_t speed = t;
    size_t timeTravelling = time - t;
    return speed * timeTravelling > max_dist;
}

size_t parse_int_ignoring_whitespaces(char *ptr) {
    size_t i = 0;
    char digit[25] = ""; 
    ptr = consume_whitespace(ptr);

    while(*ptr != '\0' && *ptr != '\n') {
        ptr = consume_whitespace(ptr);
        if (isdigit(*ptr)) {
            printf("digit found: %s\n", digit);
            digit[i++] = *ptr;
        }
        ptr += 1; 
    }

    size_t num;
    sscanf(digit, "%zu", &num);
    return num;
}

int main() {
    size_t output_p1 = 1;
    size_t output_p2 = 1;
    char line[LINE_MAX];
    size_t times[5] = {0};
    size_t distances[5] = {0};

    fgets(line, LINE_MAX, stdin);
    parse_list(&line[5], times);
    size_t max_time = parse_int_ignoring_whitespaces(&line[5]);

    fgets(line, LINE_MAX, stdin);
    parse_list(&line[9], distances);
    size_t max_dist = parse_int_ignoring_whitespaces(&line[8]);

    printf("max time = %zu, dist = %zu\n", max_time, max_dist);

    // part 1 - brute force
    // for (size_t i = 0; i < 5 && times[i] != 0 && distances[i] != 0; i++) { 
        // size_t timesExceeded = 0;
        // size_t time = times[i];
        // size_t max_dist = distances[i];
        // 
        // for (size_t t = 0; t < time; t++) {
            // if (condition(t, time, max_dist)) {
                // timesExceeded += 1;
            // }
        // }
        // if (timesExceeded > 0) {
            // output_p1 *= timesExceeded;
        // }
    // }

    size_t timesExceeded = 0;
    size_t time = max_time;

    for (size_t i = 0; i < time; i++) {
        int cond = condition(i, max_time, max_dist);
        if (cond) {
            timesExceeded += 1;
        }
    }

    printf("Part 1: %zu, Part 2: %zu\n", output_p1, timesExceeded);
    return 0;
}
