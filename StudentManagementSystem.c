#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program. Goodbye!\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "ab");

    if (fp == NULL) { printf("Error opening file.\n"); return; }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("Student record added successfully.\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "rb");

    if (fp == NULL) { printf("No records found. Add a student first.\n"); return; }

    printf("\n%-6s %-20s %-6s %-8s\n", "ID", "Name", "Age", "Marks");
    printf("---------------------------------------------\n");

    int found = 0;
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("%-6d %-20s %-6d %-8.2f\n", s.id, s.name, s.age, s.marks);
        found = 1;
    }
    if (!found) printf("No records found.\n");
    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int searchId, found = 0;

    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) { printf("No records found. Add a student first.\n"); return; }

    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == searchId) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n", s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student with ID %d not found.\n", searchId);
    fclose(fp);
}

void updateStudent() {
    struct Student s;
    int updateId, found = 0;

    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) { printf("No records found. Add a student first.\n"); return; }

    printf("Enter Student ID to update: ");
    scanf("%d", &updateId);

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == updateId) {
            printf("Enter new Name: ");
            scanf(" %49[^\n]", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            printf("Student record updated successfully.\n");
            break;
        }
    }
    if (!found) printf("Student with ID %d not found.\n", updateId);
    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    int deleteId, found = 0;

    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) { printf("No records found. Add a student first.\n"); return; }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) { printf("Error creating temporary file.\n"); fclose(fp); return; }

    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteId);

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == deleteId) { found = 1; continue; }
        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) printf("Student record deleted successfully.\n");
    else printf("Student with ID %d not found.\n", deleteId);
}