#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"

void Open_Read(File* file_, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fail to open the file.\n");
        return;
    }

    file_->count = 0;
    while (fgets(file_->lines[file_->count], MAX_LENGTH, file) != NULL) {
        file_->count++;
    }
    fclose(file);
    printf("Successfully open %s.\n", filename);
}

void Display(const File* file_) {
    printf("File:\n");
    for (int i = 0; i < file_->count; i++) {
        printf(" %-3d| %s", i + 1, file_->lines[i]);
    }
    printf("\n");
}

int Search(const File* file_, const char* word) {
    for (int i = 0; i < file_->count; i++) {
        char* position = strstr(file_->lines[i], word);
        if (position != NULL) {
            printf("Successfully found:\n %s \n ", word);
            printf("in line %-3d: %d    %s\n", i + 1, position - file_->lines[i], file_->lines[i]);
            return i;
        }
    }
    printf("Fail to find %s.\n", word);
    return -1;
}

void Replace(File* file_, const char* old_word, const char* new_word) {
    for (int i = 0; i < file_->count; i++) {
        char* position = strstr(file_->lines[i], old_word);
        if (position != NULL) {
            char t[MAX_LENGTH];
            strncpy(t, file_->lines[i], position - file_->lines[i]);
            t[position - file_->lines[i]] = '\0';
            strcat(t, new_word);
            strcat(t, position + strlen(old_word));
            strcpy(file_->lines[i], t);
            printf("Successfully replace \n%s\n with \n%s\n at line %-3d.\n", old_word, new_word, i + 1);
        }
    }
}

void Add(File* file_, const char* new_line) {
    if (file_->count >= MAX_LINES) {
        printf("Fail to add line.\n");
        return;
    }
    strcpy(file_->lines[file_->count], new_line);
    strcat(file_->lines[file_->count], "\n");
    file_->count++;
    printf("Successfully added line to the last.\n");
}

void Delete(File* file_, const int line_number) {
    if (line_number <= 0 || line_number > file_->count) {
        printf("Invalid line number.\n");
        return;
    }
    for (int i = line_number - 1; i < file_->count - 1; i++) {
        strcpy(file_->lines[i], file_->lines[i + 1]);
    }
    file_->count--;
    printf("Successfully deleted Line %-3d.\n", line_number);
}

void Save(const File* file_, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Fail to save.\n");
        return;
    }
    for (int i = 0; i < file_->count; i++) {
        fputs(file_->lines[i], file);
    }
    fclose(file);
    printf("Successfully saved %s.\n",filename);
}
