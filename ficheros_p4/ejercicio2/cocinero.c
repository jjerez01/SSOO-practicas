#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define M 10

int finish = 0;
int* caldero;
sem_t *m;
sem_t *empty;
sem_t* full;

void putServingsInPot(int servings)
{
	printf(" antes de llenar caldero: %d\n", *caldero);
	*caldero += M;
	printf("Llenando caldero %d\n", *caldero);
}

void cook(void)
{
	while(!finish) {

		sem_wait(empty);

		putServingsInPot(M);

		sem_post(full);
	}

}

void handler()
{
	printf("en teoria me tengo que morir\n");
	munmap(caldero,sizeof(int));
	sem_destroy(m);
	sem_destroy(empty);
	sem_destroy(full);
	shm_unlink("/shmpath"); //para eliminar el "fichero de mentira" de la memoria
	finish = 1;
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc != 1) {
		fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
		exit(EXIT_FAILURE);
	}


	int shd = shm_open("/shmpath", O_CREAT | O_EXCL | O_RDWR,S_IRUSR | S_IWUSR);
	if (shd == -1)
		err(EXIT_FAILURE, "open /shbuf");
	ftruncate(shd,sizeof(int)); // para poner el tamaño de la memoria compartida ( en esta caso el de un int)
	
	caldero= (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,MAP_SHARED, shd, 0);
	*caldero = 0;
	//el tamaño de memoria que se va a compartir es lo que ocupe un int por ello en el parametro de tamaño es sizeof(int)


	
	m = sem_open("m_sem",O_CREAT,0700,1);
	
	empty = sem_open("empty_sem", O_CREAT, 0700, 0);
	
	full = sem_open("full_sem",O_CREAT,0700,0);

	signal(SIGINT,handler);//se le llama asi ya que signal necesita UN PUNTERO A FUNCION que es sin parentesis

	cook();

	return 0;
}

