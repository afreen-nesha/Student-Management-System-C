#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int roll;
    char name[50];
    float cgpa;
} Student;

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n1. Add\n2. View\n3. Update\n4. Delete\n5. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) addStudent();
        else if (choice == 2) viewStudents();
        else if (choice == 3) updateStudent();
        else if (choice == 4) deleteStudent();
        else if (choice == 5) break;
    }

    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) return;

    Student *s = malloc(sizeof(Student));
    if (!s) return;

    printf("Roll: ");
    scanf("%d", &s->roll);

    printf("Name: ");
    scanf("%49s", s->name);

    printf("CGPA: ");
    scanf("%f", &s->cgpa);

    fwrite(s, sizeof(Student), 1, fp);

    free(s);
    fclose(fp);
    printf("Added\n");
}

void viewStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No data\n");
        return;
    }

    Student *s = malloc(sizeof(Student));
    if (!s) return;

    while (fread(s, sizeof(Student), 1, fp) == 1) {
        printf("%d %s %.2f\n", s->roll, s->name, s->cgpa);
    }

    free(s);
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return;

    int roll;
    printf("Roll: ");
    scanf("%d", &roll);

    Student *s = malloc(sizeof(Student));
    if (!s) return;

    while (fread(s, sizeof(Student), 1, fp) == 1) {
        if (s->roll == roll) {
            printf("New Name: ");
            scanf("%49s", s->name);

            printf("New CGPA: ");
            scanf("%f", &s->cgpa);

            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(s, sizeof(Student), 1, fp);
            printf("Updated\n");
            break;
        }
    }

    free(s);
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) return;

    int roll;
    printf("Roll: ");
    scanf("%d", &roll);

    Student *s = malloc(sizeof(Student));
    if (!s) return;

    while (fread(s, sizeof(Student), 1, fp) == 1) {
        if (s->roll != roll) {
            fwrite(s, sizeof(Student), 1, temp);
        }
    }

    free(s);
    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    printf("Deleted\n");
}
