#include "notebook.h"
#include <stdio.h>
#include <string.h>

void removeStrNewLine(char* str) {
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void loadNotebook(Notebook* notebook, const char* path) {
    int size;
    char buf[NAME_SIZE];
    FILE* file = fopen(path, "rt");

    if (!file) return;
    fscanf(file, "%d", &size);
    fgetc(file);
    notebook->size = size;

    for (int i = 0; i < size; i++) {
        fgets(buf, NAME_SIZE, file);
        removeStrNewLine(buf);
        strcpy(notebook->persons[i].name, buf);
        fscanf(
            file,
            "%d %d %d",
            &(notebook->persons[i].day),
            &notebook->persons[i].month,
            &notebook->persons[i].year
        );
        fgetc(file);
        fgets(buf, NAME_SIZE, file);
        removeStrNewLine(buf);
        strcpy(notebook->persons[i].phone, buf);
    }

    fclose(file);
}

Person* searchPerson(const char* name, const Notebook* notebook) {
    int size = notebook->size;
    char* buf;

    for (int i = 0; i < size; i++) {
        if ((buf = strstr(notebook->persons[i].name, name))) {
            return &notebook->persons[i];
        }
    }

    return NULL;
}
void printNotebook(const Notebook* notebook) {
    for (int i = 0; i < notebook->size; i++) {
        printf(
            "%s\n%d %d %d\n%s\n",
            notebook->persons[i].name,
            notebook->persons[i].day,
            notebook->persons[i].month,
            notebook->persons[i].year,
            notebook->persons[i].phone
        );
    }
}
