#pragma once

// ==== Types and values ====

#define MAX_CHAR_COUNT 128

typedef unsigned int uint;

// ==== List ====
typedef struct __list_entry {
    struct __list_entry* next;
    char value[MAX_CHAR_COUNT];
    char name[MAX_CHAR_COUNT];
    long date;

} ListEntry;

typedef struct __list {
    struct __list_entry* body; // Указатель на первый элемент
    uint size;
} List;

void initList(List* list);
void initEntry(ListEntry* entry, char* name, char* value, long date);
void freeList(List* list);
void addToList(List* list, ListEntry* entry);
void removeFromList(List* list, const uint index);
ListEntry* getFromList(const List* list, const uint index);

// ==== String ====
void removeNewLine(char* str);
