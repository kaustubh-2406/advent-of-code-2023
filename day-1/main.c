#include <stdio.h>
#include <string.h>

int main() {
    char input[100]; // Assuming a maximum input length of 100 characters
    int number = 0;

    char intNames[10][6] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    // reads from stdin
    while (fgets(input, sizeof(input), stdin)) {
	int i = 0;
	int start = 0;
	int end   = 0;

	int num = 0;
	char text[6];
	while(input[i] != '\0' && input[i] != '\n') {
	    // store the input[i] to num variable by converting it to integer
	    sscanf(&input[i], "%1d", &num);

	    // read 5 charcaters to check for similarity
	    if (sscanf(&input[i], "%5s", text) == 1) {
		for (int i = 0; i <= 10; i++) {
		    int len = strlen(intNames[i]);
		    if (strncmp(text, intNames[i], len) == 0) {
			num = i;
		    } 
		}
	    }

	    if (start == 0) {
		    start = num;
	    }
	    end = num;
	    i += 1;
	}
	
	number +=  start * 10 + end;
	printf("start: %d, end: %d\n", start , end);
	printf("input: %s, num: %d, acc: %d\n", input, start * 10 + end, number);
    } 

    return 0;
}
