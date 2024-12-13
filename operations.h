#define MAX_LINES 100
#define MAX_LENGTH 100

typedef struct {
    char lines[MAX_LINES][MAX_LENGTH];
    int count;
} File;

void Open_Read(File* file_, const char* filename);
void Display(const File* file_);
int Search(const File* file_, const char* word);
void Replace(File* file_, const char* old_word, const char* new_word);
void Add(File* file_, const char* new_line);
void Delete(File* file_, int line_number);
void Save(const File* file_, const char* filename);
#pragma once
