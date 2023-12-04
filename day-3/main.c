#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Symbol {
    int x, y;
    char symbol;
    struct Symbol *next;
};

struct Number {
    int start, end;
    int col;
    int number; 
    bool found;
    struct Number *next;
};

struct SymbolList {
    struct Symbol *head;
    struct Symbol *tail;
};

struct NumberList {
    struct Number *head;
    struct Number *tail;
};

void parse_input(int col, char *line, struct NumberList *nl, struct SymbolList *sl) {
    int row = 0;
    char c = line[row];

    while (c != '\0' && c != '\n') {
        if (c == '.') {
            row++;
            c = line[row];  
        } else if (!isdigit(c) && c != '.') {
            struct Symbol *s = malloc(sizeof(struct Symbol));
            s->x = row; 
            s->y = col; 
            s->symbol = c;
            s->next = NULL;

            row++;
            c = line[row];  

            if (sl->head == NULL) {
                sl->head = s;
                sl->tail = s;
                continue;
            }

            sl->tail->next = s;
            sl->tail = s;
        } else {
            char *endptr;
            int num = strtol(&line[row], &endptr, 10);
            int charsConsumed = (int)(endptr - &line[row]);

            struct Number *n = malloc(sizeof(struct Number));
            n->col = col;
            n->number = num;
            n->start = row; 
            n->end = row + charsConsumed;
            n->next = NULL;
            n->found = false;

            row += charsConsumed;
            c = line[row];

            if (nl->head == NULL) {
                nl->head = n;
                nl->tail = n;
                continue;
            }

            nl->tail->next = n;
            nl->tail = n;
        }
    }
}

// constants
const int LINE_MAX = 200;

int main() {
    char line[LINE_MAX];

    int col = 0;
    struct SymbolList sl = { .head = NULL, .tail = NULL };
    struct NumberList nl = { .head = NULL, .tail = NULL };

    while (fgets(line, LINE_MAX, stdin)) {
        parse_input(col, line, &nl, &sl);
        col++;
    }

    int symb_count = 0;
    struct Symbol *symbol_iter;
    symbol_iter = sl.head;
    while(symbol_iter != NULL) {
        symbol_iter = symbol_iter->next;
        symb_count += 1;
    }

    int num_count = 0;
    struct Number *number_iter;
    number_iter = nl.head;
    while(number_iter != NULL) {
        number_iter = number_iter->next;
        num_count += 1;
    }

    struct Number *iter = nl.head;
    while (iter != NULL) {
        struct Symbol *iter_sym = sl.head;
        while (iter_sym != NULL && iter_sym->y < iter->col + 2 && !iter->found) {
            for (int i = iter->start - 1; i < iter->end + 1; i++) {
                int row = iter_sym->x;
                int col = iter_sym->y;
                if (
                    row == i &&
                    (col == iter->col - 1 || col == iter->col || col == iter->col + 1 )
                ) {
                    iter->found = true;
                    break;
                }
            }

            iter_sym = iter_sym->next;
        }

        iter = iter->next;
    }

    int sum_p1 = 0;
    int sum_p2 = 0;

    struct Number *temp = nl.head;
    while (temp != NULL) {
        if (temp->found) {
            sum_p1 += temp->number;
        }
        temp = temp->next;
    }
    
    struct Symbol *t = sl.head;
    while (t != NULL) {
        if (t->symbol == '*') {
            int row = t->x;
            int col = t->y;
            printf("=============== symbol found: (%d, %d)\n",  row, col);

            int found = 0;
            int product = 1;
            struct Number *iter = nl.head;
            while (iter != NULL) {
                int i = iter->start;
                int j = iter->end;
                int k = iter->col;

                if (
                    (row >= i - 1) && (row <= j) &&
                    (col >= k - 1) && (col <= k + 1)
                ) {
                    printf("found = %d, product = %d number found: (%d-%d, %d) = %d\n", found, product, i, j, k, iter->number);
                    found += 1;
                    product *= iter->number;
                }

                if (found == 2) { 
                    printf("found = %d, product = %d, sum = %d =============\n", found, product, sum_p2);
                    sum_p2 += product;
                    break; 
                }

                iter = iter->next;
            }
        }
        
        t = t->next;
    }

    printf("=============\nPart 1: %d, Part 2: %d\n", sum_p1, sum_p2);
    return 0;
}
