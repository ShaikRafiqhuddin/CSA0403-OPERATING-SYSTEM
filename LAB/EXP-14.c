/*
 * EXP-14: Organise files using a Single Level Directory structure.
 */
#include <stdio.h>
#include <string.h>

#define MAX 20

struct file {
    char name[30];
    int size;
};

struct file directory[MAX];
int count = 0;

void create_file() {
    if (count >= MAX) {
        printf("Directory full!\n");
        return;
    }
    printf("Enter file name: ");
    scanf("%s", directory[count].name);
    printf("Enter file size: ");
    scanf("%d", &directory[count].size);
    count++;
    printf("File created successfully.\n");
}

void delete_file() {
    char name[30];
    int i, found = -1;
    printf("Enter file name to delete: ");
    scanf("%s", name);
    for (i = 0; i < count; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("File not found!\n");
        return;
    }
    for (i = found; i < count - 1; i++) {
        directory[i] = directory[i + 1];
    }
    count--;
    printf("File deleted successfully.\n");
}

void display_directory() {
    printf("\n%-20s%-10s\n", "File Name", "Size");
    for (int i = 0; i < count; i++) {
        printf("%-20s%-10d\n", directory[i].name, directory[i].size);
    }
}

void search_file() {
    char name[30];
    printf("Enter file name to search: ");
    scanf("%s", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            printf("File found: %s, Size: %d\n", directory[i].name, directory[i].size);
            return;
        }
    }
    printf("File not found!\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n2. Delete File\n3. Search File\n4. Display Directory\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: search_file(); break;
            case 4: display_directory(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
