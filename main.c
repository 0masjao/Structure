#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

struct student {
    char name[20];
    char surname[20];
    int age;
    char group[20];
};

struct student student_array[MAX_STUDENTS];
int student_count = 0;

// лол кек копирование строки
void copy_string(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// лол кек для сравнения строк
int compare_strings(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// лол кек для добавления студента
void add_student() {
    if (student_count < MAX_STUDENTS) {
        printf("Enter student's name: ");
        scanf("%s", student_array[student_count].name);
        printf("Enter student's surname: ");
        scanf("%s", student_array[student_count].surname);
        printf("Enter student's age: ");
        scanf("%d", &student_array[student_count].age);
        printf("Enter student's group: ");
        scanf("%s", student_array[student_count].group);
        student_count++;
    } else {
        printf("Student list is full.\n");
    }
}

// Функция для модификации студента
void modify_student() {
    int index;
    printf("Enter the student's index to modify (0 to %d): ", student_count - 1);
    scanf("%d", &index);

    if (index >= 0 && index < student_count) {
        printf("Enter new name: ");
        scanf("%s", student_array[index].name);
        printf("Enter new surname: ");
        scanf("%s", student_array[index].surname);
        printf("Enter new age: ");
        scanf("%d", &student_array[index].age);
        printf("Enter new group: ");
        scanf("%s", student_array[index].group);
    } else {
        printf("Invalid index.\n");
    }
}

// лол кек сравнения для сортировки
int compareByName(const void *a, const void *b) {
    return compare_strings(((struct student *)a)->name, ((struct student *)b)->name);
}

int compareBySurname(const void *a, const void *b) {
    return compare_strings(((struct student *)a)->surname, ((struct student *)b)->surname);
}

int compareByAge(const void *a, const void *b) {
    return (((struct student *)a)->age - ((struct student *)b)->age);
}

// лол кек для сортировки студентов
void sort_students() {
    int choice;
    printf("Sort by: \n1) Name\n2) Surname\n3) Age\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            qsort(student_array, student_count, sizeof(struct student), compareByName);
            break;
        case 2:
            qsort(student_array, student_count, sizeof(struct student), compareBySurname);
            break;
        case 3:
            qsort(student_array, student_count, sizeof(struct student), compareByAge);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// лол кек для выбора студентов по группе
void select_group() {
    char selected_group[20];
    printf("Enter the group (e.g., PX.22, PX.23): ");
    scanf("%s", selected_group);

    struct student group_students[MAX_STUDENTS];
    int group_count = 0;

    for (int i = 0; i < student_count; i++) {
        if (compare_strings(student_array[i].group, selected_group) == 0) {
            group_students[group_count++] = student_array[i];
        }
    }

    if (group_count == 0) {
        printf("No students found in this group.\n");
    } else {
        int choice;
        printf("Sort selected group by: \n1) Name\n2) Surname\n3) Age\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                qsort(group_students, group_count, sizeof(struct student), compareByName);
                break;
            case 2:
                qsort(group_students, group_count, sizeof(struct student), compareBySurname);
                break;
            case 3:
                qsort(group_students, group_count, sizeof(struct student), compareByAge);
                break;
            default:
                printf("Invalid choice.\n");
                return;
        }
        // конклюсон отсортированной группы
        printf("Sorted group:\n");
        for (int i = 0; i < group_count; i++) {
            printf("%s %s, Age: %d, Group: %s\n", group_students[i].name, group_students[i].surname, group_students[i].age, group_students[i].group);
        }
    }
}

// лол кек для удаления студента
void delete_student() {
    int index;
    printf("Enter the student's index to delete (0 to %d): ", student_count - 1);
    scanf("%d", &index);

    if (index >= 0 && index < student_count) {
        for (int i = index; i < student_count - 1; i++) {
            student_array[i] = student_array[i + 1];
        }
        student_count--;
        printf("Student deleted.\n");
    } else {
        printf("Invalid index.\n");
    }
}

// лол кек для вывода всех студентов
void print_students() {
    for (int i = 0; i < student_count; i++) {
        printf("%d) %s %s, Age: %d, Group: %s\n", i, student_array[i].name, student_array[i].surname, student_array[i].age, student_array[i].group);
    }
}

// менюшка
int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1) Add student\n");
        printf("2) Modify student\n");
        printf("3) Sort students\n");
        printf("4) Select group\n");
        printf("5) Delete student\n");
        printf("6) Print all students\n");
        printf("0) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                modify_student();
                break;
            case 3:
                sort_students();
                break;
            case 4:
                select_group();
                break;
            case 5:
                delete_student();
                break;
            case 6:
                print_students();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}