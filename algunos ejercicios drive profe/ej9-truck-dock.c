#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define TRUCKS 3
#define WORKERS 10
#define NP 10


char* progname;



pthread_mutex_t mtx;
pthread_cond_t space, loaded, dempty;
unsigned char  dock_empty = 1; // funciona como bool. 1 -> cierto, 0 ->falso
int truck_space;

void enter_dock(int id) {
	printf(">>>>>> Camión %d entra al dock >>>>>>>\n",id);
}

void delivery(int id) {
	printf("<<<<<<<<< Camión %d sale para reparto <<<<<<<\n",id);
	sleep(4);
}

int  get_parcel(int id) {
 static int parcelNumber = 0;
 int p;
pthread_mutex_lock(&mtx);
p=parcelNumber;
parcelNumber++;
pthread_mutex_unlock(&mtx);
printf(" >>>>>>Operario  %d va a buscar paquete %d >>>>>> \n",id,p);

return p; 
}

void load_parcel(int id, int p) {
printf(" <<<<<<<<< Operario  %d carga el paquete %d. Quedan %d huecos en el camión  <<<<<<<<< \n",id,p,truck_space);

}

void *truck(void *arg)
{
  	int id = (int) arg;
  	while (1) { 
		pthread_mutex_lock(&mtx); 
		while (!dock_empty)
			pthread_cond_wait(&dempty, &mtx); 
		truck_space = NP; 
		dock_empty = 0; 
		pthread_cond_broadcast(&space);

		enter_dock(id);

		while (truck_space)
			 pthread_cond_wait(&loaded, &mtx);
		dock_empty = 1; 
		pthread_cond_signal(&dempty); 
		pthread_mutex_unlock(&mtx);

   		delivery(id);
  	}	
}

void *worker(void *arg)
{
	int id = (int) arg; 
	int p;
	while (1) {
		p = get_parcel(id);

		pthread_mutex_lock(&mtx);
		while (dock_empty || truck_space < 1)
			pthread_cond_wait(&space, &mtx); truck_space--;

		load_parcel(id, p);

		if (truck_space == 0) 
			pthread_cond_broadcast(&loaded);
   
   		pthread_mutex_unlock(&mtx);
	}
}


int main(int argc, char *argv[])
{
	int n,i;
	char *endptr;
	pthread_t workers[WORKERS];
	pthread_t trucks[TRUCKS];

	progname = argv[0];

	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&dempty, NULL);
	pthread_cond_init(&space, NULL);
	pthread_cond_init(&loaded, NULL);

	for (i = 0; i < WORKERS; i++)
		pthread_create(&workers[i], NULL, worker, (void*) i);

	for (i = 0; i < TRUCKS; i++)
		pthread_create(&trucks[i], NULL, truck, (void*) i);

	for (i = 0; i < WORKERS; i++)
		pthread_join(workers[i], NULL);

	for (i = 0; i < TRUCKS; i++)
		pthread_join(trucks[i], NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&space);
	pthread_cond_destroy(&dempty);
	pthread_cond_destroy(&loaded);
	return 0;
}
