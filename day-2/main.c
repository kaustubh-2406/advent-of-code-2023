#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// [r, g, b]
typedef int Turn[3];
typedef int Ball[3];

char* parse_ball(char *endptr, Ball ball) {
    char *end = endptr;

    end += 1; // space
    int n = strtol(end, &end, 10);
    end += 1; // space

    // check for red, blue, green
    char color[5];
    sscanf(end, "%5c", color);
    if (strncmp(color, "red", 3) == 0) {
        ball[0] = n;
        end += 3; 
    } else if (strncmp(color, "green", 6) == 0) {
        ball[1] = n;
        end += 5; 
    } else if (strncmp(color, "blue", 4) == 0) {
        ball[2] = n;
        end += 4; 
    } else {
        printf("some differnt color found: \"%s\"\n", color);
        exit(1);
    }

    // read ","
    if (strncmp(end, ",", 1) == 0) {
        end += 1;
    }

    return end;
}

char* parse_turn(char *endptr, Turn t) {
    char *end = endptr;

    while (*end != ';' && *end != '\n') {
        Ball b = { 0, 0, 0 };
        end = parse_ball(end, b);

        t[0] += b[0];
        t[1] += b[1];
        t[2] += b[2];
    }

    end += 1; // semicolon
    return end;
}

// constants
const int LINE_MAX = 200;
const int RED_BALLS = 12;
const int BLUE_BALLS = 14;
const int GREEN_BALLS = 13;

int main() {
    int sum = 0;
    char line[LINE_MAX];


    while (fgets(line, LINE_MAX, stdin)) {
        printf("line: %s\n", line);

        bool isValid = true;
        char* endptr;
        long game = strtol(&line[5], &endptr, 10);
        printf("game = %ld\n", game);

        // ignore ": "
        endptr += 1;

        while (*endptr != '\n' && *endptr != '\0') {
            Turn t = {0, 0, 0};
            endptr = parse_turn(endptr, t);
            printf("turn: red = %d, green = %d, blue = %d\n", t[0], t[1], t[2]);
            if (t[0] > RED_BALLS || t[1] > GREEN_BALLS || t[2] > BLUE_BALLS) {
                isValid = false;
            }
        }

        if (isValid) {
            sum += game;
        }

        printf("\n=================================== score = %d\n", sum);
    }

    printf("\nScore: %d\n", sum);
    return 0;
}
