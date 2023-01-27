#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <pthread.h>

// Maximo de nodos del grafo
#define MAXPROC 16

typedef struct{
    int valid;              // Booleano para marcar validez (1: Si, 0: No)
    int next[MAXPROC];      // Array de booleanos para los sucesores del grafo
    int id;                 // Identificador
    int puede;              // Booleano para la sincronizacion
    int padre[MAXPROC];     // Padres han terminado la ejecucion 0: SI 1:NO
} task;

// task* tasks;             // Array dinamico 
task tasks[MAXPROC];        // Array normal

pthread_t threads[MAXPROC]; // Hilos

pthread_mutex_t m;          // Cerrojo
pthread_cond_t listo;       // variable de condicion

// FUNCION QUE IMPRIME EL GRAFO
void print_graph(task* tasks, int n){
	int i,j;
    
	for(i = 0; i < n; i++){
		if(!tasks[i].valid) continue;
		printf("%d: ", tasks[i].id);
		for(j = 0; j < n; j++){
			if(tasks[i].next[j]) printf("%d ", j);
		}
		printf("\n");
	}
}

// FUNCION QUE PASA LOS HILOS
void* task_body(void* arg) {
    task *t = (task*) arg;
    int id = t->id;

	wait_for_predecesors(id, t);
	printf("Task %d running\n", id);
	notify_succesors(id, t);

	return NULL;	
}

//
void wait_for_predecesors(int id, task* t){
    pthread_mutex_lock(&m);

    // Mientras que no pueda, se queda esperando
    while(!t->puede){
        pthread_cond_wait(&listo,&m);
    }

    // Recorre los hijos del nodo que puede imprimir,
    // para cambiar el array de booleanos de padre.
    // Es decir, quita los predecesores de los nodos hijos
    for(int j = 0; j < MAXPROC; j++) {        
        if(t->next[j]) tasks[j].padre[t->id] = 0;        
    }

    pthread_mutex_unlock(&m);
}

void notify_succesors(int id, task* t){
    pthread_mutex_lock(&m);
    
    // Despierta a todos los hilos, para que intenten imprimir
    pthread_cond_broadcast(&listo);

    // Solo entra en los hijos del nodo. 
    // Cambia el bool de los hijos si ya no tiene predecesores que esperar 
    for(int j = 0; j < MAXPROC; j++) {        
        if(t->next[j]){
            // Si un nodo hijo no tiene mas padres por esperar, cambia el 
            // bool puede a 1, para que puede imprimir
            // Recorre los nodos viendo si quedan mas padres por terminar        
            tasks[j].puede = 1;
            for(int k = 0; k < MAXPROC; k++){
                if(tasks[j].padre[k]) tasks[j].puede = 0; 
            }
        }
    }

    pthread_mutex_unlock(&m);
}

int main(int argc, char* argv[]) {
    int i,j;    
    //char temp[50], aux;
    //int tam;
    
    // Abre el fichero   
    FILE* f;
    f = fopen("grafo.txt","r");
    if(f == NULL){
        printf("No se ha podido abrir el fichero\n");
        exit(1);
    }

    /*Asigna memoria
    tasks = (task*)malloc(MAXPROC*sizeof(task));
    if (tasks == NULL){
        printf("No se ha podido reservar memoria\n");
        exit(1);
    }*/

    int id = 0, m;
    // Recorre el fichero hasta que llega al final
    while(!feof(f)) {    
        // Lee del fichero y almacena en variables
        // Ej: 4,2,1,5      id:4, m:2 (numero de padres)           
        fscanf(f, "%d,%d", &id, &m);
        tasks[i].id = id;
        tasks[i].valid = 1;   
        // Si no tiene padres, puede imprimir (Sincronizacion)     
        if(m == 0) tasks[i].puede = 1;
        else tasks[i].puede = 0;
        
        int predecesor;
        for(j = 0; j < m; j++) {
            fscanf(f,",%d", &predecesor);            
            tasks[predecesor].next[tasks[i].id] = 1;   
             
            // Pone a 1 el array de padres (Sincronizacion)
            tasks[i].padre[predecesor] = 1;                   
        }        
        
        i++;
    }     
    
    
    print_graph(tasks, i);
    fclose(f);   

    // Crea los hilos
    for(j = 0; j < i; j++) {             
        pthread_create(&threads[j], NULL, task_body, &tasks[j]);        
    }

    // Elimina los hilos
    for(j = 0; j < i; j++) {
       pthread_join(threads[j], NULL);     
    }    

    return 0;
}