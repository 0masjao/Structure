#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_students(struct student** students) {
    FILE* file = fopen("database.txt", "r");
    if (!file) return 0;

    int count = 0;
    char name[50], surname[50], group[50];
    int age;

    struct student* list = NULL;

    while (fscanf(file, "%s %s %d %s", name, surname, &age, group) == 4) {
        list = realloc(list, (count + 1) * sizeof(struct student));
        list[count].name = strdup(name);
        list[count].surname = strdup(surname);
        list[count].age = age;
        list[count].group = strdup(group);
        count++;
    }

    fclose(file);
    *students = list;
    return count;
}

void print_students(struct student* students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %s, age %d, group %s\n",
               students[i].name, students[i].surname,
               students[i].age, students[i].group);
    }
}

int compare_by_key(const void* a, const void* b, const char* key) {
    const struct student* sa = (const struct student*)a;
    const struct student* sb = (const struct student*)b;

    if (strcmp(key, "name") == 0) return strcmp(sa->name, sb->name);
    if (strcmp(key, "surname") == 0) return strcmp(sa->surname, sb->surname);
    if (strcmp(key, "group") == 0) return strcmp(sa->group, sb->group);
    if (strcmp(key, "age") == 0) return sa->age - sb->age;

    return 0;
}

int cmp_wrapper(const void* a, const void* b) {
    extern const char* sort_key;
    return compare_by_key(a, b, sort_key);
}

const char* sort_key;

void sort_students(struct student* students, int count, const char* key) {
    sort_key = key;
    qsort(students, count, sizeof(struct student), cmp_wrapper);
}
