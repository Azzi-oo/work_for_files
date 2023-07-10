#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

#define MAX_PATH_LENGTH 256
#define MAX_TEXT_LENGTH 255

void print_file_contents(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("n/a");
        fflush(stdin);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int file_exists(const char* path) {
    FILE* file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

int write_in_file(const char* path, const char* text) {
    FILE* file = fopen(path, "a");
    if (file == NULL) {
        printf("n/a\n");
        fflush(stdin);
        return 0;
    }
    fprintf(file, "%s\n", text);
    fclose(file);

    return 1;
}

int main() {
    char path[MAX_PATH_LENGTH];
    const char* text;
    int choice = 0;

    FILE* log_file = log_init("log.txt");

    while (choice != -1) {
        printf("Menu:\n");
        printf("1. Enter file path\n");
        printf("2. Enter text to append to file\n");
        printf("-1. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        if (choice == 1) {
            printf("Enter file path: ");
            scanf("%s", path);

            if (strcmp(path, "-1") == 0) {
                choice = -1;
                continue;
            }

            printf("File contents:\n");
            print_file_contents(path);
        } else if (choice == 2) {
            printf("Enter file path: ");
            scanf("%s", path);

            if (strcmp(path, "-1") == 0) {
                choice = -1;
                continue;
            }
            if (!file_exists(path)) {
                printf("n/a\n");
                continue;
            }
            printf("Enter text to append: ");
            char inputText[MAX_TEXT_LENGTH + 1];
            scanf("%255s", inputText);

            if (strcmp(inputText, "-1") == 0) {
                choice = -1;
                continue;
            }

            text = inputText;

            if (write_in_file(path, text)) {
                printf("File contents after appending:\n");
                print_file_contents(path);
                
                logcat(log_file, "File contents after appending", INFO);
            }
        }

        printf("\n");
    }

    log_close(log_file);

    return 0;
}
