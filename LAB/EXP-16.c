/*
 * EXP-16: Implementing Random Access File for processing
 * employee details.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"

struct Employee {
    int emp_id;
    char name[30];
    float salary;
};

void add_employee() {
    FILE *fp = fopen(FILENAME, "r+b");
    if (fp == NULL) {
        fp = fopen(FILENAME, "w+b");
    }

    struct Employee e;
    printf("Enter Employee ID: ");
    scanf("%d", &e.emp_id);
    printf("Enter Employee Name: ");
    scanf("%s", e.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &e.salary);

    fseek(fp, (e.emp_id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&e, sizeof(struct Employee), 1, fp);

    fclose(fp);
    printf("Employee record added at position %d.\n", e.emp_id);
}

void read_employee() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("File does not exist!\n");
        return;
    }

    int id;
    printf("Enter Employee ID to read: ");
    scanf("%d", &id);

    struct Employee e;
    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&e, sizeof(struct Employee), 1, fp);

    if (e.emp_id == id) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", e.emp_id, e.name, e.salary);
    } else {
        printf("Record not found!\n");
    }

    fclose(fp);
}

void display_all() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("File does not exist!\n");
        return;
    }

    struct Employee e;
    printf("\n%-10s%-20s%-10s\n", "ID", "Name", "Salary");
    while (fread(&e, sizeof(struct Employee), 1, fp)) {
        if (e.emp_id != 0)
            printf("%-10d%-20s%-10.2f\n", e.emp_id, e.name, e.salary);
    }

    fclose(fp);
}

int main() {
    int choice;
    do {
        printf("\n1. Add Employee\n2. Read Employee (Random Access)\n3. Display All\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee(); break;
            case 2: read_employee(); break;
            case 3: display_all(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
