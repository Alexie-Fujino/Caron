#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

void menu() {
    printf("File Management Menu\n");
    printf("=======================\n");
    printf("0. Save and Exit\n");
    printf("1. Open File\n");
    printf("2. Display File\n");
    printf("3. Search Word\n");
    printf("4. Replace Word\n");
    printf("5. Add Line\n");
    printf("6. Delete Line\n");
    printf("=======================\n");
    printf("\nEnter your choice: ");
}

int main() {
    File file_ = { .count = 0 };
    char filename[100]= "1.c";
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 0: {
            system("cls");
            Save(&file_, filename);
            system("pause");
            exit(0);
            }
        case 1: {
            system("cls");
            Open_Read(&file_, filename);
            getchar();
            break;
            }
        case 2: {
            system("cls");
            Display(&file_);
            getchar();
            break;
            }
        case 3: {
            system("cls");
            char word[50];
            printf("Enter the word to search: ");
            scanf("%s", word);
            Search(&file_, word);
            getchar();
            break;
            }
        case 4: {
            system("cls");
            char old_word[50], new_word[50];
            printf("Enter the word to be replaced: \n");
            scanf("%s", old_word);
            printf("Enter the new word: \n");
            scanf("%s", new_word);
            Replace(&file_, old_word, new_word);
            getchar();
            break;
            }
        case 5: {
            system("cls");
            char new_line[MAX_LENGTH];
            printf("Enter the new line: \n");
            fgets(new_line, MAX_LENGTH, stdin);
            Add(&file_, new_line);
            getchar();
            break;
            }
        case 6: {
            system("cls");
            int line_number;
            printf("Enter the line number to be deleted: ");
            scanf("%d", &line_number);
            Delete(&file_, line_number);
            getchar();
            break;
            }
        default: {
            system("cls");
            printf("Invalid choice! Please enter again.\n");
            getchar();
            }
        }
        while (1) {
            printf("\nType ENTER to return to the main menu.\n");
            if (getchar()) break;
        }
        system("cls");
    }
    return 0;
}
