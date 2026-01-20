#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    int marks;
};

/* Check duplicate roll */
int isDuplicate(int roll) {
    FILE *fp = fopen("students.csv", "r");
    struct Student s;

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d,%49[^,],%d\n",
                  &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* Update student */
void updateStudent(int roll) {
    FILE *fp = fopen("students.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    struct Student s;
    int found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fscanf(fp, "%d,%49[^,],%d\n",
                  &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            printf("Enter new marks: ");
            scanf("%d", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d,%s,%d\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
        printf("Record updated successfully.\n");
    else
        printf("Roll number not found.\n");
}

/* Delete student */
void deleteStudent(int roll) {
    FILE *fp = fopen("students.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    struct Student s;
    int found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fscanf(fp, "%d,%49[^,],%d\n",
                  &s.roll, s.name, &s.marks) == 3) {
        if (s.roll != roll) {
            fprintf(temp, "%d,%s,%d\n", s.roll, s.name, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("Roll number not found.\n");
}

int main() {
    struct Student s;
    FILE *fp;
    int choice, roll;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student Marks\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter Roll Number: ");
            scanf("%d", &s.roll);

            if (isDuplicate(s.roll)) {
                printf("Roll number already exists!\n");
                continue;
            }

            printf("Enter Name (single word): ");
            scanf("%s", s.name);

            printf("Enter Marks: ");
            scanf("%d", &s.marks);

            fp = fopen("students.csv", "a");
            fprintf(fp, "%d,%s,%d\n", s.roll, s.name, s.marks);
            fclose(fp);

            printf("Student added successfully.\n");
        }

        else if (choice == 2) {
            fp = fopen("students.csv", "r");
            if (fp == NULL) {
                printf("No records found.\n");
                continue;
            }

            printf("\nRoll\tName\tMarks\n");
            while (fscanf(fp, "%d,%49[^,],%d\n",
                          &s.roll, s.name, &s.marks) == 3) {
                printf("%d\t%s\t%d\n", s.roll, s.name, s.marks);
            }
            fclose(fp);
        }

        else if (choice == 3) {
            printf("Enter roll number to update: ");
            scanf("%d", &roll);
            updateStudent(roll);
        }

        else if (choice == 4) {
            printf("Enter roll number to delete: ");
            scanf("%d", &roll);
            deleteStudent(roll);
        }

        else if (choice == 5) {
            printf("Exiting program.\n");
            exit(0);
        }

        else {
            printf("Invalid choice!\n");
        }
    }
}