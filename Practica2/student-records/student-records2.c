#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_NIF 9

typedef struct {
    int student_id; 
    char NIF[MAX_CHARS_NIF+1];  
    char* first_name;
    char* last_name;
} student_t;

student_t* parse_records(char* records[], int* nr_records) {
    // Split records by ":" and store them in a student_t struct
    student_t* students = malloc(sizeof(student_t) * (*nr_records));
    for (int i = 0; i < *nr_records; i++) {
        char* current_record = records[i];
        char* current_field = strtok(current_record, ":");
        students[i].student_id = atoi(current_field);
        current_field = strtok(NULL, ":");
        strcpy(students[i].NIF, current_field);
        current_field = strtok(NULL, ":");
        students[i].first_name = current_field;
        current_field = strtok(NULL, ":");
        students[i].last_name = current_field;
    }
    return students;
}

void create_file(char* filename, student_t* students, int nr_records) {
    // Create the file and write the header (number of records) and the student records
    FILE* file = fopen(filename, "wb");
    int header = nr_records;
    fwrite(&header, sizeof(int), 1, file);
    for (int i = 0; i < nr_records; i++) {
        student_t current_student = students[i];
        fwrite(&current_student.student_id, sizeof(int), 1, file);
        fwrite(current_student.NIF, sizeof(char), MAX_CHARS_NIF+1, file);
        int first_name_len = strlen(current_student.first_name) + 1;
        fwrite(&first_name_len, sizeof(int), 1, file);
        fwrite(current_student.first_name, sizeof(char), first_name_len, file);
        int last_name_len = strlen(current_student.last_name) + 1;
        fwrite(&last_name_len, sizeof(int), 1, file);
        fwrite(current_student.last_name, sizeof(char), last_name_len, file);
    }
    fclose(file);
}

void list_file(char* filename) {
    // Open the file and read the header and student records
    FILE* file = fopen(filename, "rb");
    int nr_records;
    fread(&nr_records, sizeof(int), 1, file);
    for (int i = 0; i < nr_records; i++) {
        student_t current_student;
        fread(&current_student.student_id, sizeof(int), 1, file);
        fread(current_student.NIF, sizeof(char), MAX_CHARS_NIF+1, file);
        int first_name_len;
        fread(&first_name_len, sizeof(int), 1, file);
        current_student.first_name = malloc(sizeof(char) * first_name_len);
        fread(current_student.first_name, sizeof(char), first_name_len, file);
        int last_name_len;
        fread(&last_name_len, sizeof(int), 1, file);
        current_student.last_name = malloc(sizeof(char) * last_name_len);
        fread(current_student.last_name, sizeof(char), last_name_len, file);
        printf("Student ID: %d, NIF: %s, First Name: %s, Last Name: %s\n", current_student.student_id, current_student.NIF, current_student.first_name, current_student.last_name);
        free(current_student.first_name);
        free(current_student.last_name);
    }
    fclose(file);
}   
void add_records(char* filename, student_t* students, int nr_records) {
    // Open the file in append mode and write the student records at the end of the file
    FILE* file = fopen(filename, "ab");
    for (int i = 0; i < nr_records; i++) {
    student_t current_student = students[i];
    fwrite(&current_student.student_id, sizeof(int), 1, file);
    fwrite(current_student.NIF, sizeof(char), MAX_CHARS_NIF+1, file);
    int first_name_len = strlen(current_student.first_name) + 1;
    fwrite(&first_name_len, sizeof(int), 1, file);
    fwrite(current_student.first_name, sizeof(char), first_name_len, file);
    int last_name_len = strlen(current_student.last_name) + 1;
    fwrite(&last_name_len, sizeof(int), 1, file);
    fwrite(current_student.last_name, sizeof(char), last_name_len, file);
    }
    fclose(file);
}
int query_by_id(char* filename, int student_id) {
    // Open the file and read the header and student records
    // Return 1 if a student with the given ID is found, 0 otherwise
    FILE* file = fopen(filename, "rb");
    int nr_records;
    fread(&nr_records, sizeof(int), 1, file);
    for (int i = 0; i < nr_records; i++) {
        student_t current_student;
        fread(&current_student.student_id, sizeof(int), 1, file);
        if (current_student.student_id == student_id) {
            fclose(file);
            return 1;
        }
        //fread(current_student.NIF, sizeof(char), MAX_CH(int), 1, file);
        fread(current_student.NIF, sizeof(char), MAX_CHARS_NIF+1, file);
        int first_name_len;
        fread(&first_name_len, sizeof(int), 1, file);
        current_student.first_name = malloc(sizeof(char) * first_name_len);
        fread(current_student.first_name, sizeof(char), first_name_len, file);
        int last_name_len;
        fread(&last_name_len, sizeof(int), 1, file);
        current_student.last_name = malloc(sizeof(char) * last_name_len);
        fread(current_student.last_name, sizeof(char), last_name_len, file);
        free(current_student.first_name);
        free(current_student.last_name);
    }
    fclose(file);
    return 0;
}

int query_by_nif(char* filename, char* NIF) {
    // Open the file and read the header and student records
    // Return 1 if a student with the given NIF is found, 0 otherwise
    FILE* file = fopen(filename, "rb");
    int nr_records;
    fread(&nr_records, sizeof(int), 1, file);
    for (int i = 0; i < nr_records; i++) {
        student_t current_student;
        fread(&current_student.student_id, sizeof(int), 1, file);
        fread(current_student.NIF, sizeof(char), MAX_CHARS_NIF+1, file);
        if (strcmp(current_student.NIF, NIF) == 0) {
            fclose(file);
            return 1;
        }
        int first_name_len;
        fread(&first_name_len, sizeof(int), 1, file);
        current_student.first_name = malloc(sizeof(char) * first_name_len);
        fread(current_student.first_name, sizeof(char), first_name_len, file);
        int last_name_len;
        fread(&last_name_len, sizeof(int), 1, file);
        current_student.last_name = malloc(sizeof(char) * last_name_len);
        fread(current_student.last_name, sizeof(char), last_name_len, file);
        free(current_student.first_name);
        free(current_student.last_name);
    }
    fclose(file);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: missing arguments\n");
        printf("Usage: %s -f file [ -h | -l | -c | -a | -q [ -i|-n ID] ] ] [ list of records ]\n", argv[0]);
        return 1;
    }

    char* filename = NULL;
    int option = 0;
    int student_id = 0;
    char* NIF = NULL;
    student_t* students = NULL;
    int nr_records = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            // Set the file name
            printf("esaq");
            i++;
            filename = argv[i];
        } else if (strcmp(argv[i], "-h") == 0) {
            // Print usage information
            printf("Usage: %s -f file [ -h | -l | -c | -a | -q [ -i|-n ID] ] ] [ list of records ]\n", argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-l") == 0) {
            // List the contents of the file
            option = 1;
        } else if (strcmp(argv[i], "-c") == 0) {
            // Create a new file with the given records
            printf("esaqa");
            option = 2;
            i++;
            students = parse_records(argv + i, &nr_records);
            i += nr_records - 1;
        } else if (strcmp(argv[i], "-a") == 0) {
            // Add records to the end of the file
            option = 3;
            i++;
            students = parse_records(argv + i, &nr_records);
            i += nr_records - 1;
        } else if (strcmp(argv[i], "-q") == 0) {
            // Query for a specific record
            option = 4;
            i++;
            if (strcmp(argv[i], "-i") == 0) {
                // Query by student ID
                i++;
                student_id = atoi(argv[i]);
            } else if (strcmp(argv[i], "-n") == 0) {
                // Query by NIF
                i++;
                NIF = argv[i];
            } else {
                printf("Error: invalid query option\n");
                return 1;
            }
        } else {
            printf("Error: invalid option\n");
            return 1;
        }
    }

    if (filename == NULL) {
        printf("Error: missing file name\n");
        return 1;
    }

    if (option == 1) {
        list_file(filename);
    } else if (option == 2) {
        create_file(filename, students, nr_records);
        printf("%d records written successfully\n", nr_records);
    } else if (option == 3) {
        add_records(filename, students, nr_records);
        printf("%d records written successfully\n", nr_records);
    } else if (option == 4) {
        if (student_id != 0) {
            int found = query_by_id(filename, student_id);
            if (found) {
                printf("Student with ID %d found\n", student_id);
            } else {
                printf("Student with ID %d not found\n", student_id);
            }
        } 
        else if (NIF != NULL) {
            int found = query_by_nif(filename, NIF);
            if (found) {
                printf("Student with NIF %s found\n", NIF);
            } else {
                printf("Student with NIF %s not found\n", NIF);
            }
        }
        
    }
    return 0;
}
