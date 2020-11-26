#include "utils.h"
#include <stdlib.h>
#include <string.h>

// ==== List ====

void initList(List* list) {
    list->body = NULL;
    list->size = 0;
}

void initEntry(ListEntry* entry, char* name, char* value, long date) {
    entry->next = NULL;
    entry->date = date;
    strcpy(entry->name, name);
    strcpy(entry->value, value);
}

void freeLast(ListEntry* entry) {
    if (entry->next == NULL) {
        free(entry);
    } else {
        freeLast(entry->next);
    }
}

void freeList(List* list) {
    if (list->body == NULL) {
        free(list);
        return;
    }
    
    freeLast(list->body);
    free(list);
}

void addToList(List* list, ListEntry* entry) {
    ListEntry* e;

    if (list->body == NULL) {
        list->body = entry;
        list->size = 1;
        return;
    }

    e = list->body;

    while (e->next != NULL) {
        e = e->next;
    }

    e->next = entry;
    list->size++;
}
void removeFromList(List* list, const uint index) {
    ListEntry *entry = NULL, *next = NULL, *old = NULL;

    if (index >= list->size)
        return;
    
    if (index == 0) {
        next = list->body->next;
        free(list->body);
        list->body = next;
        list->size--;
        return;
    }

    for (int i = 0; i <= index; i++) {
        if (entry == NULL) {
            entry = list->body;
            old   = list->body;
        } else {
            old = entry;
            entry = entry->next;
        }
    }
    next = entry->next;
    free(entry);
    old->next = next;
    list->size--;
}

ListEntry* getFromList(const List* list, const uint index) {
    ListEntry* res = NULL;

    if (index >= list->size) return NULL;

    res = list->body;
    for (int i = 1; i <= index; i++) {
        res = res->next;
    }

    return res;
}

// ==== String ====

void removeNewLine(char* str) {
    str[strlen(str)-1] = '\0';
}
