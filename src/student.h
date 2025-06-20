#ifndef STUDENT_H
#define STUDENT_H

struct student {
    char* name;
    char* surname;
    int age;
    char* group;
};

int load_students(struct student** students);
void save_students(struct student* students, int count);
void print_students(struct student* students, int count);
void sort_students(struct student* students, int count, const char* key);

#endif
