#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  ./student_db print [group] [sorted] [key]\n");
        fprintf(stderr, "  ./student_db sort <key>\n");
        return 1;
    }

    struct student* students = NULL;
    int count = load_students(&students);

    if (count == 0) {
        printf("No students found.\n");
        return 0;
    }

    if (strcmp(argv[1], "print") == 0) {
        int sorted = 0;
        const char* group = NULL;
        const char* key = NULL;

        if (argc >= 3 && strcmp(argv[2], "sorted") != 0) {
            group = argv[2];
        }

        if ((argc == 4 && strcmp(argv[2], "sorted") == 0) ||
            (argc == 5 && strcmp(argv[3], "sorted") == 0)) {
            sorted = 1;
            key = argv[argc - 1];
        }

        if (sorted && key) {
            sort_students(students, count, key);
        }

        if (group) {
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(students[i].group, group) == 0) {
                    printf("%s %s, age %d, group %s\n",
                           students[i].name, students[i].surname,
                           students[i].age, students[i].group);
                    found = 1;
                }
            }
            if (!found) {
                printf("No students in group %s.\n", group);
            }
        } else {
            print_students(students, count);
        }

    } else if (strcmp(argv[1], "sort") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: ./student_db sort <key>\n");
        } else {
            sort_students(students, count, argv[2]);
            print_students(students, count);
        }

    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
    }

    for (int i = 0; i < count; i++) {
        free(students[i].name);
        free(students[i].surname);
        free(students[i].group);
    }
    free(students);
    return 0;
}
