#ifndef DEFS_H
#define DEFS_H

#define MAX_CHARS_NIF  9
#define MAX_PASSWD_LINE  255

typedef enum {
	STUDENT_ID,
	NIF,
	FIRST_NAME,
	LAST_NAME,
} token_id_t; 

typedef struct {
	int student_id; 
	char NIF[MAX_CHARS_NIF+1];	
	char* first_name;
	char* last_name;
} student_t;

#endif
