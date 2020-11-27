#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include "notebook.h"

void clear() {
    system("cls");
}


int main() {
    Notebook* notebook = (Notebook*)malloc(sizeof(Notebook));
    Person* search = NULL;
    char buf[NAME_SIZE];

    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadNotebook(notebook, "notebook.txt");

    while (1) {
        clear();
        printf("==================== Notebook ====================\n");
        printNotebook(notebook);
        printf("==================================================\n");
        printf("[Search (q to exit)]: ");
        fgets(buf, NAME_SIZE, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (strcmp(buf, "q") == 0) break;
        search = searchPerson(buf, notebook);
        if (!search) {
            printf("Not found :(\n");
        } else {
            printf(
                "Found: %s %d.%d.%d phone: %s\n",
                search->name,
                search->day,
                search->month,
                search->year,
                search->phone
            );
        }
        printf("Press ENTER to continue\n");
        fgets(buf, NAME_SIZE, stdin);
    }

    free(notebook);

    return 0;
}
