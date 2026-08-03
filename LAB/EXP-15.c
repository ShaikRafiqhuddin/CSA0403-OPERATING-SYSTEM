/*
 * EXP-15: Organise files using a Two Level Directory structure.
 * Each user has their own directory containing their files.
 */
#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 20

struct file {
    char name[30];
    int size;
};

struct user {
    char username[30];
    struct file files[MAX_FILES];
    int file_count;
};

struct user users[MAX_USERS];
int user_count = 0;

int find_user(char *uname) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, uname) == 0) return i;
    }
    return -1;
}

void create_user() {
    if (user_count >= MAX_USERS) {
        printf("Maximum users reached!\n");
        return;
    }
    printf("Enter new username: ");
    scanf("%s", users[user_count].username);
    users[user_count].file_count = 0;
    user_count++;
    printf("User directory created.\n");
}

void create_file() {
    char uname[30];
    printf("Enter username: ");
    scanf("%s", uname);
    int idx = find_user(uname);
    if (idx == -1) {
        printf("User not found!\n");
        return;
    }
    if (users[idx].file_count >= MAX_FILES) {
        printf("User directory full!\n");
        return;
    }
    struct file *f = &users[idx].files[users[idx].file_count];
    printf("Enter file name: ");
    scanf("%s", f->name);
    printf("Enter file size: ");
    scanf("%d", &f->size);
    users[idx].file_count++;
    printf("File created for user %s.\n", uname);
}

void display_directory() {
    printf("\n--- Two Level Directory Structure ---\n");
    for (int i = 0; i < user_count; i++) {
        printf("\nUser: %s\n", users[i].username);
        printf("%-20s%-10s\n", "File Name", "Size");
        for (int j = 0; j < users[i].file_count; j++) {
            printf("%-20s%-10d\n", users[i].files[j].name, users[i].files[j].size);
        }
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Create User\n2. Create File\n3. Display Directory\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_user(); break;
            case 2: create_file(); break;
            case 3: display_directory(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
