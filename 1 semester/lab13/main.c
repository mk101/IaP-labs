#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(char* word) {
    int len = strlen(word);

    for (int i = 0; i < len/2; i++) {
        if (word[i] != word[len-1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    char words[1024];
    char* cur = NULL;

    printf("Input words: ");
    fgets(words, 1024, stdin);

    words[strlen(words)-1] = ' '; // '\n' -> ' '

    cur = strtok(words, " ");
    while (cur) {
        if (isPalindrome(cur)) {
            printf("%s\n", cur);
        }
        cur = strtok(NULL, " ");
    }

    return 0;
}