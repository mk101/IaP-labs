#pragma once

#define PERSON_SIZE 1024
#define NAME_SIZE   256

typedef struct {
    char name[NAME_SIZE];
    int year, month, day;
    char phone[14];
} Person;

typedef struct {
    Person persons[PERSON_SIZE];
    int size;
} Notebook;

void loadNotebook(Notebook* notebook, const char* path);
Person* searchPerson(const char* name, const Notebook* notebook);
void printNotebook(const Notebook* notebook);
