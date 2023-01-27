#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 10

char* progname;

int caldero = 0;
sem_t m, empty, full;

void putServingsInPot(int m)
{
	caldero += m;
	printf("Llenando caldero %d\n", caldero);
}

int getServingsFromPot(int id)
{
	printf("Salvaje %d sirviendo ración del caldero %d\n",
			id, caldero);
	caldero--;
}

void eat(int id)
{
	printf("Salvaje %d comiendo\n", id);
	sleep(rand() % 5);
}

void* salvaje(void* arg)
{
	int id = (int) arg;

	while(1) {
		sem_wait(&m);
		if (caldero == 0) {
			sem_post(&empty);
			sem_wait(&full);
		}
		getServingsFromPot(id);
		sem_post(&m);
		eat(id);
	}

}

void* cocinero(void* arg)
{
	while(1) {
		sem_wait(&empty);
		putServingsInPot(M);
		sem_post(&full);
	}
}


void usage() {
	printf("%s Num_de_salvajes\n", progname);
}

int main(int argc, char *argv[])
{
	int n,i;
	char *endptr;
	pthread_t *tid;
	pthread_t tid_cook;

	progname = argv[0];

	if (argc < 2) {
		usage();
		exit(EXIT_FAILURE);
	}

	n = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0'){
		usage();
		exit(EXIT_FAILURE);
	}

	tid = malloc(n * sizeof(pthread_t));
	if (tid == NULL){
		perror("malloc tid");
		exit(EXIT_FAILURE);
	}

	sem_init(&m, 0, 1);
	sem_init(&empty, 0, 0);
	sem_init(&full, 0, 0);

	for (i = 0; i < n; i++)
		pthread_create(&tid[i], NULL, salvaje, (void*) i);

	pthread_create(&tid_cook, NULL, cocinero, NULL);

	for (i = 0; i < n; i++)
		pthread_join(tid[i], NULL);

	pthread_join(tid_cook, NULL);

	sem_destroy(&m);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}
