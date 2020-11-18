#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct __bracket {
    bool isRound; // ()
    bool isOpen;
    size_t column, row;
    struct __bracket* pair;
} Bracket;

size_t getBracketCount(const char* path);
void setPairBracket(Bracket* brackets, const size_t size, const bool isRound, Bracket* bracket, const int start);

int main() {
    FILE* file;
    Bracket* brackets;
    size_t size, i, row, column;
    char cur;

    size = getBracketCount("source.c");
    brackets = (Bracket*)malloc(size * sizeof(Bracket));
    file = fopen("source.c", "rt");

    i = 0;

    row = 1;
    column = 1;

    while ((cur = fgetc(file)) != EOF) {
        if (cur == '(') {
            brackets[i].isRound = true;
            brackets[i].isOpen = true;
            brackets[i].row = row;
            brackets[i].column = column;
            brackets[i].pair = NULL;

            i++;
        }
        else if (cur == ')') {
            brackets[i].isRound = true;
            brackets[i].isOpen = false;
            brackets[i].row = row;
            brackets[i].column = column;
            setPairBracket(brackets, size, true, &brackets[i], i-1);
            i++;
        }
        else if (cur == '{') {
            brackets[i].isRound = false;
            brackets[i].isOpen = true;
            brackets[i].row = row;
            brackets[i].column = column;
            brackets[i].pair = NULL;
            i++;
        }
        else if (cur == '}') {
            brackets[i].isRound = false;
            brackets[i].isOpen = false;
            brackets[i].row = row;
            brackets[i].column = column;
            setPairBracket(brackets, size, false, &brackets[i], i-1);
            i++;
        }

        if (cur == '\n' || cur == '\r') {
            row++;
            column = 1;
        }
        else {
            column++;
        }
    }

    for (int j = 0; j < i; j++) {
        if (brackets[j].isOpen) {
            if (brackets[j].isRound) {
                printf("k ");
            }
            else {
                printf("f ");
            }
            printf("%zu %zu : ", brackets[j].column, brackets[j].row);
            if (brackets[j].pair != NULL) {
                printf("%zu %zu\n", brackets[j].pair->column, brackets[j].pair->row);
            }
            else {
                printf("no\n");
            }
        }
        else {
            if (brackets[j].pair == NULL) {
                if (brackets[j].isRound) {
                    printf("k ");
                }
                else {
                    printf("f ");
                }
                printf("no : %zu %zu\n", brackets[j].column, brackets[j].row);
            }
        }
    }

    free(brackets);
    fclose(file);
    return 0;
}

size_t getBracketCount(const char* path) {
    size_t count = 0;
    char cur = ' ';
    FILE* f = fopen(path, "rt");

    while ((cur = fgetc(f)) != EOF) {
        if (cur == '(' || cur == ')' || cur == '{' || cur == '}')
            count++;
    }

    fclose(f);
    return count;
}

void setPairBracket(Bracket* brackets, const size_t size, const bool isRound, Bracket* bracket, const int start) {
    for (int i = start; i >= 0; i--) {
        if (brackets[i].isRound == isRound && brackets[i].pair == NULL) {
            brackets[i].pair = bracket;
            bracket->pair = &brackets[i];
            return;
        }
    }
    bracket->pair = NULL;
}