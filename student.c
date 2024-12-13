#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STROR 100

int n = 0;

typedef struct {
    char num[20];
    char name[20];
    int score;
}student;
student s[MAX_STROR];


void menu()
{
    printf("Student Score Manager System");
    printf("\n");
    printf("=============================");
    printf("\n");
    printf("0  Exit\n");
    printf("1  Input information\n");
    printf("2  Display information\n");
    printf("3  Sort with Scores\n");
    printf("4  Delete information\n");
    printf("5  Search Score\n");
    printf("6  Alter information\n");
    printf("7  Save Changes\n");
    printf("=============================");
    printf("\n\n");
    printf("Input choice:");
}

void input() {
    int i, t;
    printf("Input the number of students to add: ");
    scanf("%d", &t);
    if (n + t > MAX_STROR) {
        printf("The number should be limited to 100!\n");
        return;
    }
    student* p = s + n;
    for (i = 0; i < t; i++) {
        printf("Input No. %d student's number: ", i + 1);
        scanf("%s", p->num);
        printf("Input No. %d student's name: ", i + 1);
        scanf("%s", p->name);
        printf("Input No. %d student's score: ", i + 1);
        scanf("%d", &p->score);
        printf("\n");
        p++;
    }
    n += t;
}

void display() {
    student* p = s;
    printf("Number       Name       Score\n");
    printf("==============================\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s  %-10s  %d\n", p->num, p->name, p->score);
        p++;
    }
}

void sort() {
    student t;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((s + j)->score < (s + j + 1)->score) {
                t = *(s + j);
                *(s + j) = *(s + j + 1);
                *(s + j + 1) = t;
            }
        }
    }
    display();
}

void cutoff() {
    char t[20];
    printf("Input the student's number you wanna delete: ");
    scanf("%s", t);
    student* p = s;
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(p->num, t) == 0) {
            break;
        }
        p++;
    }
    if (i == n) {
        printf("The number doesn't exist!\n");
    }
    else {
        for (i = 0; i < n - 1; i++) {
            *(s + i) = *(s + i + 1);
        }
        n--;
        printf("Successfully deleted!\n");
        display();
    }
}

void search() {
    char name[20];
    printf("Input the student's name you wanna search: ");
    scanf("%s", name);
    student* p = s;
    for (int i = 0; i < n; i++) {
        if (strcmp(p->name, name) == 0) {
            printf("Successfully found!\n");
            printf("==============================\n");
            printf("%-10s  %-10s  %d\n", p->num, p->name, p->score);
            return;
        }
        p++;
    }
    printf("Failed to find the student!\n");
}

int search_num(char* k) {
    printf("Input the student's number you wanna search: ");
    scanf("%s", k);
    student* p = s;
    for (int i = 0; i < n; i++) {
        if (strcmp(p->num, k) == 0) {
            return i;
        }
        p++;
    }
    return -1;
}

void alter() {
    char k[20];
    int num2 = search_num(k);
    if (num2 == -1) {
        printf("Please input the right number!\n");
        return;
    }
    student* p = s + num2;
    printf("1. Number\n");
    printf("2. Name\n");
    printf("3. Score\n");
    printf("\nDecide which do you wanna alter: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        printf("Input the new number: ");
        scanf("%s", p->num);
        printf("Successfully altered!\n");
        break;
    case 2:
        printf("Input the new name: ");
        scanf("%s", p->name);
        printf("Successfully altered!\n");
        break;
    case 3:
        printf("Input the new score: ");
        scanf("%d", &p->score);
        printf("Successfully altered!\n");
        break;
    default:
        printf("Wrong input! Please input again.\n");
    }
    display();
}

void save() {
    FILE* fout = fopen("student.txt", "w");
    if (fout == NULL) {
        printf("Failed to open the file!\n");
        exit(1);
    }
    fprintf(fout, "%d\n", n);
    student* p = s;
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%-10s  %-10s  %d\n", p->num, p->name, p->score);
        p++;
    }
    fclose(fout);
    printf("Successfully saved!\n");
}

void initial() {
    FILE* fin = fopen("student.txt", "r");
    if (fin == NULL) {
        printf("Failed to open the file!\n");
        return;
    }
    fscanf(fin, "%d", &n);
    student* p = s;
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%s %s %d", p->num, p->name, &p->score);
        p++;
    }
    fclose(fin);
}

int main()
{
	int a;
	initial();
	while (1)
	{
		menu();
		scanf("%d", &a);
		if (a == 0) break;
		switch (a)
		{
		case 1:
			system("cls");
			input();
			getchar();
			break;
		case 2:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
				display();
			getchar();
			break;
		case 3:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
			{
				sort();
				printf("Succeessfully sorted");
			}
			getchar();
			break;
		case 4:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
				cutoff();
			getchar();
			break;
		case 5:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
				search();
			getchar();
			break;
		case 6:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
			{
				alter();
			}
			getchar();
			break;
		case 7:
			system("cls");
			if (n == 0)
				printf("The list is empty!");
			else
				save();
			getchar();
			break;
		default:
			system("cls");
			printf("Wrong input!Please input again:\n");
			getchar();
		}
		while (1)
		{
			printf("\nType ENTER to return to the main menu\n");
			if (getchar())
				break;
		}
		system("cls");
	}
	return 0;
}