#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int* caldero;
sem_t *m, *empty, *full;

int getServingsFromPot(void)
{
	printf("Salvaje %d sirviendo ración del caldero %d\n",getpid(), *caldero);
	*caldero -= 1;
	printf("dewspues de vaciar caldero: %d\n", *caldero);
}

void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(NUMITER)
{
	int i;
	for (i = 0; i < NUMITER; i++) {
		sem_wait(m);
		if (*caldero == 0) {
			sem_post(empty);
			sem_wait(full);
		}
		getServingsFromPot();
		sem_post(m);
		eat();
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
	}
	int fd = shm_open("/shmpath", O_RDWR,S_IRUSR | S_IWUSR);
    if (fd == -1)
    	err(EXIT_FAILURE, "open /shbuf");
	ftruncate(fd,sizeof(int));
	
	caldero = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
	//el tamaño de memoria que se va a compartir es lo que ocupe un int por ello en el parametro de tamaño es sizeof(int)
	m = sem_open("m_sem",O_RDWR);
	empty = sem_open("empty_sem",0,O_RDWR);
	full = sem_open("full_sem",0,O_RDWR);

	savages(argv[1]);

	return 0;
}