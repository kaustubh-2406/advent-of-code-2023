# Day 1 learnings
- learned about reading text from stdin.

#### Fgets
- Helps read filecontent from file and store in a "buffer" (i dont know wheather the char* can be called buffer, but i call it that way).
- Stdin is also a File. So it was nice discovering it.

```c
char* fgets(char* destination, int chars_to_read, File* file) 
```

### Converting char to int
For converting char to int stumbled on a couple of approaches.

1. **Substraction by '0'**:
    - well apparrently, '4' - '0' seems a legit way to find the digit. 
    - I have done things like this in js. 
    - But i have never thought it would also exist in c.
    ```c
    int a = '4' - '0'; // this is valid
    printf("output: %d", a);
    ```

2. **atoi**:
    - atoi function is also a good way to convert a provided str into int.
    - when i was writting code, i was stuck because atoi take string and gives int output
    - but i wanted to give only one character. So, i rejected it and moved forward
    - However in hindsight, it seems obvious that i could have used a char as a pointer too.
    ```c
    int atoi(char* your_string)

    char s[20] = "1234five";
    int num = atoi(char);
    printf("output: %d", num); // output: 1234
    ```

3. **sscanf**:
    - sscanf reads the provided input and reads according to the format specifier
    - the format specifier became a huge life saver, especially during the second part.
    - %1d and %5d were two nice discoveries for me.
    ```c
    int sscanf(char* source, char* formatSpecifier, int destination);

    char s[20] = "1234five";
    int onenum;
    int number;
    sscanf(char, "%1d", onenum);
    sscanf(char, "%d", number);
    printf("output: onenum = %d, number = %d", onenum, number); // output: onenum = 1, number = 1234
    ```

### Comparining strings
1. `int strcmp(char* first, char* second) // returns, zero if equal`
1. `int strncmp(char* first, char* second, int length_to_compare) // returns, zero if equal`

### Discussion about solution
- I have looped over each character of input
    1. checked if it is an integer
    2. or if it is string one|two|three|four|five|siz|seven|eight|nine
- If i found some match then
    1. if first is not defined, set it
    2. always set the matched value in last.
