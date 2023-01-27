#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <pthread.h>

#define MAXPROC 16
#define MAX_LINE 50

typedef struct {
    int valid;  //booleano, indica si la entrada es valida (1) o no (0)
    int next[MAXPROC];  //array de booleanos para sucesores: next[i] = 1 si sale una aristahacia el nodo i
    int pred[MAXPROC];  //array de booleanos que indica quienes son los padres de los hijos
    int terminado;
    int id; //identificador/nombre de la tarea, que corresponde a su posicion en el array de nodos

}task;

pthread_mutex_t m;
pthread_cond_signal ready;
task t[MAXPROC];
int cantidad = 0;

void* task_body(void* arg) {
    task *t = (task*) arg;
    int id = t->id;

	wait_for_predecesors(id, t);
	printf("Task %d running\n", id);
	notify_succesors(id, t);

	return NULL;	
}

void wait_for_predecesors(int id,task* t){
    pthread_mutex_lock(&m);
    while(!t[id].valid){
        pthread_cond_wait(&ready,&m);
    }

    for(int i = 0; i < MAXPROC;i++){
        if(t->next[i] == 1){
            t[i].padre[t->id] = 0;
        }
    }
    pthread_mutex_unlock(&m);
}

void* notify_sucesors(void*arg,task* t){

    pthread_mutex_lock(&m);
    pthread_cond_broadcast(&listo);

    for(int j = 0; j < MAXPROC; j++) {        
        if(t->next[j]){ 
            tasks[j].puede = 1;
            for(int k = 0; k < MAXPROC; k++){
                if(tasks[j].padre[k]) tasks[j].puede = 0; 
            }
        }
    }

    pthread_mutex_unlock(&m);

}

void parse_file(char filename[]){

    FILE* fd;
    

    fd = fopen("fic.txt","r");
    if(fd == NULL){
        printf("No se ha podido abrir el fichero\n");
        exit(1);
    }

    int i = 0;
    int id;
    int m;
    while(!feof(fd)){
        fscanf(fd,"%d,%d",&id,&m);
        t[i].id = id;
        t[i].valid = 1; 
        
        if(m == 0) t[id].valid = 1;
        int j;
        int sucesor;
        for(j = 0; j < m;j++){
            
            fscanf(fd,",%d",&sucesor);
            t[sucesor].next[t[i].id] = 1;
            t[i].pred[sucesor] = 1;

        }
        i++;
        cantidad++;
        
    }
    fclose(fd);
		
}

void point_graph(){
    int i,j;
    for(i = 0; i < cantidad; i++){
        if(!t[i].valid) continue;
        printf("%d: ",t[i].id);
        for(j = 0; j < cantidad; j++){   
            if(t[i].next[j]){
                printf("%d ",j);
                
            }
        }
        printf("\n");
    }
}



int main(int argc, char *argv[]){

    pthread *tid;

    if(argc != 2){
        perror("error en argumentos");
        exit(1);
    }
    //printf("%s",argv[1]);
    parse_file(argv[1]);
    point_graph(MAXPROC);

    tid = malloc(cantidad * sizeof(pthread_t));
	if (tid == NULL){
		perror("malloc tid");
		exit(EXIT_FAILURE);
	}
    
    pthread_mutex_init(&m, NULL);
	pthread_cond_init(&ready, NULL);

    for (i = 0; i < n; i++)
        pthread_create(&tid[i], NULL, task_body,&tasks[j]);

	for (i = 0; i < n; i++)
		pthread_join(tid[i], NULL);

    return 0;
}
