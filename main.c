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
    Line* lines = NULL; // 声明结构数组
    int line_count = 0;
    char filename[100];
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
        case 0: {
            system("cls");
            Save(lines, line_count, filename);
            Free(lines, line_count);
            system("pause");
            exit(0);
        }
        case 1: {
            system("cls");
            printf("Please enter the filname:");
            scanf("%s", filename);
            Open_Read(&lines, &line_count, filename);
            break;
            }
        case 2: {
            system("cls");
            Display(lines, line_count);
            break;
            }
        case 3: {
            system("cls");
            char word[50];
            printf("Enter the word to search: ");
            scanf("%s", word);
            Search(lines, line_count, word);
            break;
            }
        case 4: {
            system("cls");
            char old_word[50], new_word[50];
            printf("Enter the word to be replaced: \n");
            scanf("%s", old_word);
            printf("Enter the new word: \n");
            scanf("%s", new_word);
            Replace(lines, line_count, old_word, new_word);
            break;
            }
        case 5: {
            system("cls");
            int line_number;
            printf("Enter the line number to be added before: ");
            scanf("%d", &line_number);
            getchar(); // 重要！取消换行符，下方同理
            char new_line[MAX_LENGTH];
            printf("Enter the new line: \n");
            fgets(new_line, MAX_LENGTH, stdin);
            Add(&lines, &line_count, new_line, line_number);
            break;
            }
        case 6: {
            system("cls");
            int line_number;
            printf("Enter the line number to be deleted: ");
            scanf("%d", &line_number);
            Delete(&lines, &line_count, line_number);
            break;
            }
        default: {
            system("cls");
            printf("Invalid choice! Please enter again.\n");
            }
        }
        while (1) {
            getchar();
            printf("\nType ENTER to return to the main menu.\n");
            if (getchar()) break;
        }
        system("cls");
    }
    return 0;
}
