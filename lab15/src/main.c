#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "io.h"
#include "utils.h"

void printHeader();
void printFooter(int show);

int main() {
    int key, stage, cursor;
    char name[MAX_CHAR_COUNT], value[MAX_CHAR_COUNT];
    char buf[1024];
    List* list = (List*)malloc(sizeof(List));
    ListEntry* entry = NULL;
    initList(list);
    listFromFile(list, "notes.n");
    key    = 0;
    stage  = 0;
    cursor = 0;

    setBufferedInput(false);
    while (key != KEY_QUIT) {
        clear();
        printHeader();
        if (stage == 0) {
            if (list->size == 0) {
                printf("No notes here yet. Press 'a' to add a new note\n");
            } else {
                for (int i = 0; i < list->size; i++) {
                    entry = getFromList(list, i);
                    strcpy(buf, asctime(localtime(&entry->date)));
                    removeNewLine(buf);
                    if (cursor == i) {
                        printf("> %s [%s]\n", entry->name, buf);
                    } else {
                        printf("  %s [%s]\n", entry->name, buf);
                    }
                }
            }
            printFooter(1);
        } else if (stage == 1) { // add
            entry = (ListEntry*)malloc(sizeof(ListEntry));
            setBufferedInput(true);
            
            printf("Write name of new note: ");
            fgets(name, MAX_CHAR_COUNT, stdin);
            removeNewLine(name);
            printf("Write note: ");
            fgets(value, MAX_CHAR_COUNT, stdin);
            removeNewLine(value);
            
            initEntry(entry, name, value, time(0));
            addToList(list, entry);
            setBufferedInput(false);
            printFooter(0);
        } else if (stage == 2) {
            entry = getFromList(list, cursor);
            strcpy(buf, asctime(localtime(&entry->date)));
            removeNewLine(buf);
            printf("====%s====\n%s\n[%s]\n", entry->name, entry->value, buf);
            printFooter(0);
        }
        
        key = getKey();
        if (key == KEY_A && stage == 0) {
            stage = 1;
        } else if (key == KEY_B) {
            stage = 0;
        } else if (key == KEY_R && stage == 0) {
            removeFromList(list, cursor);
            cursor = 0;
        } else if (key == KEY_DOWN && cursor < list->size-1) {
            cursor++;
        } else if (key == KEY_UP && cursor > 0) {
            cursor--;
        } else if (key == KEY_ENTER && stage == 0) {
            if (list->size == 0) continue;
            stage = 2;
        }
    }
    setBufferedInput(true);
    
    listToFile(list, "notes.n");

    freeList(list);
    return 0;
}

void printHeader() {
    printFor('=', 20);
    printf(" Nots ");
    printFor('=', 20);
    printf("\n");
}

void printFooter(int show) {
    if (show) {
        printf("========[q - quit a - add r - remove]=========\n");
    } else {
        printf("=============[q - quit b - back]==============\n");
    }
}