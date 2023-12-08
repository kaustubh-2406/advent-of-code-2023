#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char* consume_whitespace(char *ptr) {
    while (*ptr == ' ') {
        ptr += 1;
    }
    return ptr;
}

void print_int_list(size_t *list, int max) {
    for (int i = 0; i < max; i++) {
        printf("%zu ", list[i]);
    }
}

char* parse_list(char *ptr, size_t *list) {
    ptr = consume_whitespace(ptr);
    
    int i = 0;
    while (*ptr != '\n' && *ptr != '\0') {
        int num = strtol(ptr, &ptr, 10);
        list[i++] = num;
        ptr = consume_whitespace(ptr);
    }

    return ptr;
}

// constants
const int LINE_MAX = 500;

struct GroupItem {
    size_t curr_start;
    size_t next_start;
    size_t count;
};

struct Group {
    int length;
    struct GroupItem *items;
};

struct GroupItem parse_line(char *ptr) {
    ptr = consume_whitespace(ptr);
    size_t next_start = strtoul(ptr, &ptr, 10);
    ptr = consume_whitespace(ptr);
    size_t curr_start = strtoul(ptr, &ptr, 10);
    ptr = consume_whitespace(ptr);
    size_t count = strtoul(ptr, &ptr, 10);
    
    struct GroupItem l = { 
        .count = count, 
        .curr_start = curr_start, 
        .next_start = next_start,
    };

    return l;
}

struct Group parse_group(char *line) {
    int i = 0;
    struct GroupItem *gil = malloc(50 * sizeof(struct GroupItem));

    fgets(line, LINE_MAX, stdin); // ignore what-to-what map.
    while(fgets(line, LINE_MAX, stdin) && *line != '\n') {
        struct GroupItem item = parse_line(line);
        gil[i++] = item;
    }

    struct Group g;
    g.length = i; 
    g.items = malloc(50 * sizeof(struct GroupItem)); 
    for (int j = 0; j < i; j++) {
        g.items[j] = gil[j];
    }
    return g;
}


void print_group(struct Group g) {
    int len = g.length;

    printf("==================== length = %d \n", len);
    for (int i = 0; i < g.length; i++) {
        printf("%d = start: %zu, count: %zu, next_start: %zu\n", i, g.items[i].curr_start, g.items[i].count, g.items[i].next_start);
    }
}

size_t get_next_value(struct Group g, size_t num) {
    for (int i = 0; i < g.length; i++) {
        struct GroupItem gi = g.items[i];
        if (gi.curr_start <= num && gi.curr_start + gi.count > num - 1) {
            size_t diff = num - gi.curr_start;
            return gi.next_start + diff;
        }
    }

    return num;
}

int main() {
    size_t output_p1 = 0;
    size_t output_p2 = 0;
    char line[LINE_MAX];

    int i = 0;
    size_t seeds[30] = {0};

    // seeds
    fgets(line, LINE_MAX, stdin);
    parse_list(&line[6], seeds);

    fgets(line, LINE_MAX, stdin); // ignore empty line.

    struct Group soil = parse_group(line);
    struct Group fertilizer = parse_group(line);
    struct Group water = parse_group(line);
    struct Group light = parse_group(line);
    struct Group temp = parse_group(line);
    struct Group humidity = parse_group(line);
    struct Group location = parse_group(line);

    size_t min_dist = 18446744073709551615;
    for (int i = 0; i < 30 && seeds[i] != 0; i++) {
        size_t num = seeds[i];
        num = get_next_value(soil, num);
        num = get_next_value(fertilizer, num);
        num = get_next_value(water, num);
        num = get_next_value(light, num);
        num = get_next_value(temp, num);
        num = get_next_value(humidity, num);
        num = get_next_value(location, num);

        if (num < min_dist) {
            min_dist = num;
        }
    }

    output_p1 = min_dist;
    min_dist = 18446744073709551615;
    printf("===========================\n");
    print_int_list(seeds, 30);
    printf("\n===========================\n");
   
    for (int i = 0; i < 30 && seeds[i] != 0; i += 2) {
        size_t num = seeds[i];
        size_t count = seeds[i + 1];
        printf("num = %zu, count = %zu\n", num, count);

        for (int j = 0; j < count; j++) {
            num = seeds[i] + j;
            num = get_next_value(soil, num);
            num = get_next_value(fertilizer, num);
            num = get_next_value(water, num);
            num = get_next_value(light, num);
            num = get_next_value(temp, num);
            num = get_next_value(humidity, num);
            num = get_next_value(location, num);

            if (num < min_dist) {
                min_dist = num;
            }
        }
    }
    output_p2 = min_dist;

    printf("Part 1: %zu, Part 2: %zu\n", output_p1, output_p2);
    return 0;
}
