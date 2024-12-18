#define MAX_LENGTH 100

typedef struct {
    char* line;  // 行内容
    int count;   // 行号
} Line;

// 函数声明
// 打开并读取文件内容，存储在动态分配的 Line 结构体数组中
void Open_Read(Line** lines, int* line_count, const char* filename);
// 保存文件内容到指定的文件中
void Save(Line* lines, int line_count, const char* filename);
// 释放动态分配的内存
void Free(Line* lines, int line_count);
// 显示文件内容
void Display(Line* lines, int line_count);
// 查找文件中指定的单词，并返回所在的行号，若未找到返回 -1
void Search(Line* lines, int line_count, const char* word);
// 替换文件中指定的词为新的词
void Replace(Line* lines, int line_count, const char* old_word, const char* new_word);
// 在文件中指定位置添加一行
void Add(Line** lines, int* line_count, const char* new_line, const int line_number);
// 删除文件中指定的行
void Delete(Line** lines, int* line_count, const int line_number);

#pragma once
