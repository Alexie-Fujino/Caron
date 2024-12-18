#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

void Open_Read(Line** lines, int* line_count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fail to open the file.\n");
        return;
    }
    // ��ȡ����������line_count*Line�Ŀռ�
    char buffer[MAX_LENGTH];
    *line_count = 0;
    while (fgets(buffer, MAX_LENGTH, file) != NULL)  (*line_count)++;
    *lines = (Line*)malloc(sizeof(Line) * (*line_count));
    if (*lines == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }
    // ��ȡÿһ�в�Ϊÿ�з���strlen(buffer)+'\0'�Ŀռ�
    rewind(file); // ˢ�»�����
    for (int i = 0; i < *line_count; i++) {
        if (fgets(buffer, MAX_LENGTH, file) != NULL) {
            (*lines)[i].line = (char*)malloc(strlen(buffer) + 1);
            if ((*lines)[i].line == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }
            strcpy((*lines)[i].line, buffer);
            (*lines)[i].count = i + 1;
        }
    }
    fclose(file);
    printf("Successfully opened %s.\n", filename);
}

void Save(Line* lines, int line_count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Fail to save.\n");
        return;
    }
    for (int i = 0; i < line_count; i++) {
        fputs(lines[i].line, file);
    }
    fclose(file);
    printf("Successfully saved %s.\n", filename);
}

void Free(Line* lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        free(lines[i].line); // �ͷ�ÿһ��
    }
    free(lines);  // �ͷ� Line ����
}

void Display(Line* lines, int line_count) {
    printf("File:\n");
    for (int i = 0; i < line_count; i++) {
        printf(" %-3d| %s", lines[i].count, lines[i].line);
    }
    printf("\n");
}

void Search(Line* lines, int line_count, const char* word) {
    int found = 0;
    for (int i = 0; i < line_count; i++) {
        char* position = strstr(lines[i].line, word);
        while (position != NULL) {
            printf("Successfully found:\n %s \n ", word);
            printf("in line %-3d: %lld    %s\n", lines[i].count, position - lines[i].line, lines[i].line);
            found++;
            position = strstr(position + strlen(word), word); // ��һ��ƥ��Ĵ�
        }
    }
    if (found == 0) printf("Fail to find %s.\n", word);
    else printf("found %d matched line.", found);
}

void Replace(Line* lines, int line_count, const char* old_word, const char* new_word) {
    for (int i = 0; i < line_count; i++) {
        char* position = strstr (lines[i].line, old_word);
        while (position != NULL) {
            char t[MAX_LENGTH];
            strncpy(t, lines[i].line, position - lines[i].line);
            t[position - lines[i].line] = '\0';
            strcat(t, new_word);
            strcat(t, position + strlen(old_word));
            strcpy(lines[i].line, t);
            printf("Successfully replace \n%s\n with \n%s\n at line %-3d.\n", old_word, new_word, lines[i].count);
            position = strstr(position + strlen(new_word), old_word); // ��һ��ƥ��Ĵ�
        }
    }
}

void Add(Line** lines, int* line_count, const char* new_line, const int line_number) {
    // �����ų�
    if (line_number < 1 || line_number > *line_count + 1) {
        printf("Invalid line number.\n");
        return;
    }
    // ����һ��
    *lines = (Line*)realloc(*lines, sizeof(Line) * (*line_count + 1));
    if (*lines == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    // ֮���������ƶ�һ��
    for (int i = *line_count; i >= line_number; i--) {
        (*lines)[i] = (*lines)[i - 1];
    }
    // Ϊ���з���strlen(new_line) + '\0'�Ŀռ�
    (*lines)[line_number - 1].line = (char*)malloc(strlen(new_line) + 1);
    if ((*lines)[line_number - 1].line == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy((*lines)[line_number - 1].line, new_line);
    (*lines)[line_number - 1].count = line_number; // �������е��к�
    for (int i = line_number; i < *line_count + 1; i++) {
        (*lines)[i].count = i + 1;  // ����֮���е��к�
    }
    (*line_count)++;
    printf("Successfully added line before line %d.\n", line_number);
}

void Delete(Line** lines, int* line_count, const int line_number) {
    if (line_number <= 0 || line_number > *line_count) {
        printf("Invalid line number.\n");
        return;
    }
    // �ͷ�Ҫɾ������
    free((*lines)[line_number - 1].line);
    // �������ǰ��
    for (int i = line_number; i < *line_count; i++) {
        (*lines)[i - 1] = (*lines)[i];
    }
    // ���·����ڴ�
    *lines = (Line*)realloc(*lines, sizeof(Line) * (*line_count - 1));
    if (*lines == NULL && *line_count > 1) {
        printf("Memory reallocation failed.\n");
        return;
    }
    for (int i = line_number - 1; i < *line_count - 1; i++) {
        (*lines)[i].count = i + 1;  // ���������е��к�
    }
    (*line_count)--;
    printf("Successfully deleted Line %-3d.\n", line_number);
}

