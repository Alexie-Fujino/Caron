#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// Global file pointer
FILE *path = NULL;
// Function to display the menu
void menu(){
    printf("1. Open file\n");
    printf("2. Display file\n");
    printf("3. Search for a specific word\n");
    printf("4. Replace a specific word\n");
    printf("5. Add a line\n");
    printf("6. Delete a line\n");
    printf("7. Save and exit\n");
}
// Function to get user choice
int choose(){
    int choice;
    printf("Please enter the number of the operation you want to perform:\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("File opened\n");
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 5:
            return 5;
            break;
        case 6:
            return 6;
            break;
        case 7:
            printf("Saved and exited\n");
            return 7;
            break;
        default:
            return 0;
            break;
    }
}
// Function to perform brute-force search
int BF(const char* text, const char* word){
    if (text == NULL || word == NULL) {
        return -1; // If input is null, return -1
    }
    int text_len = strlen(text);
    int word_len = strlen(word);
    for (int textIndex = 0; textIndex <= text_len - word_len; textIndex++) {
        for (int wordIndex = 0; wordIndex < word_len; wordIndex++) {
            if (text[textIndex + wordIndex] != word[wordIndex]) {
                break; // If current character does not match, break the inner loop
            }
            if (wordIndex == word_len - 1) {
                return textIndex; // Found the word, return its starting position in the text and exit the function immediately
            }
        }
    }
    return -1; // Word not found, return -1
}
// Function to open a file
void open_file(){
    path = fopen("C://Users//rt123//Desktop//1.c", "r+");
    if (path == NULL) {
        printf("Error: File pointer is NULL.\n");
    }
}
// Function to close a file
void close_file(){
    fclose(path);
}
// Function to display the file content
void display_file(){
    if (path == NULL){
        printf("Error: File not opened.\n");
        return;
    }
    rewind(path); // Reset the file pointer to the beginning of the file
    char buffer[1024]; // Create a buffer to read file content
    while (fgets(buffer, sizeof(buffer), path) != NULL){ // Loop through the file until the end
        fputs(buffer, stdout); // Print the buffer content to standard output (usually the console)
    }
    rewind(path); // Reset the file pointer to the beginning of the file
    printf("\nFile display completed\n");
}
// Function to search for a specific word in the file
void search_word(){
    if (path == NULL){
        printf("Error: File not opened.\n");
        return;
    }
    int position;
    printf("Please enter the word you want to search:\n");
    char word[100];
    scanf("%s", word);
    char buffer[1024];
    int line = 0; // Line number
    rewind(path); // Reset the file pointer to the beginning of the file
    // Read file content into buffer
    while (fgets(buffer, sizeof(buffer), path) != NULL){
        line++;
        position = BF(buffer, word);
        if (position != -1){
            printf("Found, the word is at position: Line %d, Initial position %d\n", line, position);
            break;
        }
    }
    if (position == -1){
        printf("The specified word was not found\n");
    }
    rewind(path);
    printf("Search for a specific word completed\n");
}
// Function to replace a specific word in the file
void replace_word() {
    if (path == NULL){
        printf("Error: File not opened.\n");
        return;
    }
    char old_word[100];
    char new_word[100];
    printf("Please enter the word you want to replace:\n");
    scanf("%99s", old_word); // Limit input length to prevent buffer overflow
    printf("Please enter the new word:\n");
    scanf("%99s", new_word); // Limit input length to prevent buffer overflow
    FILE *tempFile = fopen("C://Users//rt123//Desktop//temp.txt", "w+");
    char buffer1[1024];
    char *positions = NULL;
    int line = 0;
    rewind(path); // Reset the file pointer to the beginning of the file
    while (fgets(buffer1, sizeof(buffer1), path)){
        line++;
        while ((positions = strstr(buffer1, old_word)) != NULL) {
            // Move the remaining string to make space for the new string
            memmove(positions + strlen(new_word), positions + strlen(old_word), strlen(positions + strlen(old_word)) + 1);
            // Copy the new string to the specified position
            memcpy(positions, new_word, strlen(new_word));
        }
        fputs(buffer1, tempFile);
    }
    char buffer2[1024];
    int id = fileno(path);
    rewind(path);
    rewind(tempFile);
    ftruncate(id, 0);
    int temp = line;
    while (temp--){
        fgets(buffer2, sizeof(buffer2), tempFile);
        fputs(buffer2, path);
    }
    rewind(path);
    fclose(tempFile);
    printf("Replacement of a specific word completed\n");
    printf("The effect after replacement is:\n");
    display_file();
}
// Function to add a line to the file
void add_line(){
    if (path == NULL){
        printf("Error: File not opened.\n");
        return;
    }
    FILE *paths = fopen("C://Users//rt123//Desktop//1.c", "a+");
    char buffer[1024];
    printf("Please enter the content you want to add:\n");
    scanf("%s", buffer);
    fseek(paths, 0, SEEK_END); // Move the file pointer to the end of the file
    fprintf(paths, "\n%s", buffer); // Write the new line to the file
    fclose(paths);
    printf("Addition completed\n");
    printf("The effect after addition is:\n");
    display_file(); 
}
// Function to delete a line from the file
void delete_line(){
    if (path == NULL){
        printf("Error: File not opened.\n");
        return;
    }
    FILE *tempFile = fopen("C://Users//rt123//Desktop//temp.txt", "w+");
    char buffer1[1024];
    int line = 0;
    // Calculate total number of lines in the file
    while (fgets(buffer1, 1024, path) != NULL){
        line++;
    }
    rewind(path);
    printf("Please enter the line number you want to delete:\n");
    int deleteLine;
    scanf("%d", &deleteLine);
    if (deleteLine < 1 || deleteLine > line){
        printf("The entered line number is out of range\n");
        return;
    }
    int currentLine = 0;
    while (fgets(buffer1, 1024, path) != NULL){
        currentLine++;
        if (currentLine != deleteLine){
            fputs(buffer1, tempFile);
        }
    }
    rewind(path);
    rewind(tempFile);
    char buffer2[1024];
    int id = fileno(path);
    rewind(path);
    ftruncate(id, 0);
    int temp = line - 1;
    while (temp--){
        fgets(buffer2, 1024, tempFile);
        fputs(buffer2, path);
    }
    rewind(path);
    fclose(tempFile);
    printf("The specified line has been deleted\n");
    printf("The effect after deletion is:\n");
    display_file();
}
// Function to perform the chosen operation
void opeartion(int choice){
    switch (choice){
        case 1:
            open_file();
            break;
        case 2:
            display_file();
            break;
        case 3:
            search_word();
            break;
        case 4:
            replace_word();
            break;
        case 5:
            add_line();
            break;
        case 6:
            delete_line();
            break;
        case 7:
            close_file();
            exit(0);
            break;
        default:
            printf("Invalid input, please re-enter\n");
            break;
    }
}
// Main function
int main(){
    int choice;
    while (1){
        menu();
        choice = choose();
        opeartion(choice);
    }
    return 0;
}
