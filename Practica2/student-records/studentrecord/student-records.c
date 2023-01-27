#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include "defs.h"


// fscanf, fprintf, strcat,
// strcpy, strlen, strsep
static inline char* clone_string(char* original)
{
	char* copy;
	copy=malloc(strlen(original)+1);
	strcpy(copy,original);
	return copy;
}


char* loadstr(FILE * file)
{
    char line[MAX_PASSWD_LINE+1];
    if (fgets(line, MAX_PASSWD_LINE, file) == NULL)
    {
        return NULL;
    }
    return clone_string(line);
}

void createFileWithRecords(int argc,char* argv[]){
    if (argc < 4) {
        printf("informacion incompleta.\n");
        return;
    }

    char* filename = argv[2];
    FILE* fd = fopen(filename, "w");
    if (fd == NULL) {
        printf("no se creo el archivo correctamente\n");
        return;
    }

    int num_records = argc - 3;
    fwrite(&num_records, sizeof(int), 1, fd);

    student_t* students = malloc(sizeof(student_t) * num_records);
    for (int i = 0; i < num_records; i++) {
        char* record = argv[i + 3];
        char* token;
        token = strtok(record, ":");
        sscanf(token, "%d", &students[i].student_id);
        token = strtok(NULL, ":");
        strcpy(students[i].NIF, token);
        token = strtok(NULL, ":");
        students[i].first_name = strdup(token);
        token = strtok(NULL, ":");
        students[i].last_name = strdup(token);
    }

    fwrite(students, sizeof(student_t), num_records, fd);
    fclose(fd);
    printf("%d records written successfully.\n", num_records);

}

void listEntries(student_t* entries,int nr_entries){
    if(entries == NULL){
        fprintf(stderr, "no hay entradas: ");
        perror(NULL);
        exit(1);
    }else{
        for(int i = 0; i < nr_entries;i++){
            student_t* curr_entry = &entries[i];
            printf("Entry %d\n",i);
            printf("Student id = %i\n",curr_entry->student_id);
            printf("NIF = %s\n",curr_entry->NIF);
            printf("first name = %s\n",curr_entry->first_name);
            printf("last name = %s\n\n",curr_entry->last_name);
        }
    }

}

student_t* parse_records(char* records[], int nr_records)
{
    char line[MAX_PASSWD_LINE+1];
    student_t* ret = malloc(sizeof(student_t) * nr_records);
    student_t* current_entry;
    char* lineptr;

    token_id_t token_id;
    char* atributo;

    //strsep(&records[i],":"); (char** con el &, char* con "");
    for(int i = 0; i < nr_records; i++){
        token_id = STUDENT_ID;
        lineptr = records[i];
        current_entry = &ret[i];
        while((atributo = strsep(&lineptr,":")) != NULL){
            printf("este es el estudiante %s",atributo);
            switch (token_id)
            {
                case STUDENT_ID:
                    sscanf(atributo,"%d",&current_entry->student_id);                        
                    break;
                case NIF:
                    strcpy(current_entry->NIF,atributo);
                    break;
                case FIRST_NAME:
                    current_entry->first_name = clone_string(atributo); 
                    break;
                case LAST_NAME:
                    current_entry->last_name = clone_string(atributo); 
                    break;
                default:
                    break;
            }
            
            token_id++;

            // if (token_id!=LAST_NAME) {
			//     fprintf(stderr, "no se ha procesado todas las lineas de el registro en la linea %d \n",i);
			//     return NULL;
            // }
		}
        
    }
    return ret;
}

int dump_entries(student_t* entries, int nr_entries, FILE* students)
{
    if(!entries) return EXIT_FAILURE;

    for(int i = 0; i < nr_entries;i++){

        student_t* current_entry = &entries[i];

        // para abrir el archivo (poner en otro sitio)
        // if ((options.outfile=fopen(optarg,"wx"))==NULL) {
		// 		fprintf(stderr, "The output file %s could not be opened: ",
		// 		        optarg);
		// 		perror(NULL);
		// 		exit(EXIT_FAILURE);
		// }

        fprintf(students,"%s:%s:%s:%s\n",current_entry->student_id,current_entry->NIF,current_entry->first_name,current_entry->last_name);
    }
    return EXIT_SUCCESS;
}

student_t* read_student_file(FILE* students, int* nr_entries,char* tmpname)
{

    char line[MAX_PASSWD_LINE+1];
    int line_count = 0;
    student_t* entries;

    if((students = fopen(tmpname,"r")==NULL)){
        fprintf(stderr, "el fichero no se abre: ");
		perror(NULL);
		return NULL;
    }

   //para saber cuantas lineas tiene el archivo.
   //por lo visto fgets lee hasta EOF o hasta salto de linea con lo cual es un problema pq queremos que pare en espacio
    while (fgets(line, MAX_PASSWD_LINE + 1, students) != NULL){
		line_count++;
    }

    fseek(students,0,SEEK_SET);

    entries=malloc(sizeof(student_t)*line_count);
    /* (zero fill the array of structures)
    imagino que esto es para inicializar entries todo a cero */
	memset(entries,0,sizeof(student_t)*line_count);

    student_t* parsedEntries = parse_records(entries,line_count);

    (*nr_entries) = line_count; 
    return parsedEntries;
}

int main(int argc, char *argv[])
{
    int opt;

    student_t* entries;

    while((opt = getopt(argc,argv, "hcl"))!=-1){
        switch(opt){
            case 'h':
                fprintf(stderr,"Usage: ./student-records -f file [ -h | -l | -c | -a | -q [ -i|-n ID] ] ] [ list of records ]",argv[0]);
                exit(0);
            
            case 'c':
                int nr_entries; 
                createFileWithRecords(argc,argv);
                //entries = read_student_file(fd,&nr_entries,argv[2]);
                break;
            case 'l':
                listEntries(entries,nr_entries);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}
