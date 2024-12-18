#define MAX_LENGTH 100

typedef struct {
    char* line;  // ������
    int count;   // �к�
} Line;

// ��������
// �򿪲���ȡ�ļ����ݣ��洢�ڶ�̬����� Line �ṹ��������
void Open_Read(Line** lines, int* line_count, const char* filename);
// �����ļ����ݵ�ָ�����ļ���
void Save(Line* lines, int line_count, const char* filename);
// �ͷŶ�̬������ڴ�
void Free(Line* lines, int line_count);
// ��ʾ�ļ�����
void Display(Line* lines, int line_count);
// �����ļ���ָ���ĵ��ʣ����������ڵ��кţ���δ�ҵ����� -1
void Search(Line* lines, int line_count, const char* word);
// �滻�ļ���ָ���Ĵ�Ϊ�µĴ�
void Replace(Line* lines, int line_count, const char* old_word, const char* new_word);
// ���ļ���ָ��λ�����һ��
void Add(Line** lines, int* line_count, const char* new_line, const int line_number);
// ɾ���ļ���ָ������
void Delete(Line** lines, int* line_count, const int line_number);

#pragma once
