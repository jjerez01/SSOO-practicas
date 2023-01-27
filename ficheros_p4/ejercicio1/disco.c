#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 1 //quitar
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

// tendremos una variable int nticketvip int turnovip
int turnovip = 0;
int turno = 0;
int nTicketVip = -1;
int nTicket = -1;
int hasVip = 0;

int numGente = 5;
pthread_mutex_t cerr;
pthread_cond_t libre;
pthread_cond_t lleno;

typedef struct{
	int id;
	int vip;
}arg_t;

void enter_normal_client(int id)
{
	

	while(numGente == CAPACITY|| nTicket != turno){
		pthread_cond_wait(&libre, &cerr);
	}
	printf("el cliente %d normal %d %d entra\n",id,nTicket,turno);
	numGente++;
}


void enter_vip_client(int id)
{
	
	while(numGente == CAPACITY|| nTicketVip != turnovip){
		pthread_cond_wait(&libre, &cerr);
	}
	printf("el cliente %d vip %d %d entra\n",id,nTicketVip,turnovip);
	numGente++;
}


void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}
//disco exit tiene que avisar con broadcast de que ya pueden entrar
void disco_exit(int id, int isvip)
{
	printf("el cliente %d se marcha\n",id);
	pthread_cond_broadcast(&libre);
	
	numGente--;
}


void *client(void *argvoid)
{
	
	
	arg_t* arg = (arg_t*)argvoid;
	int id = arg->id;
	int isvip = arg->vip;
	if(isvip == 0){
		sleep(2);
		/*hay varios metodos: uno es crear los vips con pthread create primero y luego los normales 
		y va todo muy fluido y otro que es el que he hecho cutre pero mesirve es crear todos a la vez, dormir los novip 
		ejecutar los vip y luego van los novip*/
	}
	if(isvip){
		nTicketVip++;
	}  
	else{

		nTicket++;
	}

	pthread_mutex_lock(&cerr);
	
	
	if (isvip){
		enter_vip_client(id);
		turnovip++;
		hasVip--;
	}
	else{
		if(hasVip == 0){
			enter_normal_client(id);
			turno++;
		}
	}


	pthread_mutex_unlock(&cerr);
	
	dance(id,isvip);
	disco_exit(id,isvip);

	
	
}

int main(int argc, char *argv[])
{
	int nClientes;
	int isvip;
	FILE* f = fopen(argv[1],"r");
	fscanf(f,"%d\n",&nClientes);
	pthread_t hilos[nClientes];
	for(int i = 0; i < nClientes;i++){
		
		fscanf(f,"%d\n",&isvip);
		printf("%d\n",isvip);
		arg_t *arg =malloc(sizeof(arg_t));
		arg->id = i;
		arg->vip = isvip;
		if(isvip == 1){
			hasVip++;
		}
		pthread_create(&hilos[i], NULL, client, arg); 

	for(int i = 0; i < nClientes;i++){
		
		pthread_join(hilos[i], NULL); //esto lo que hace es esperar a que el hilo termine
	}

	return 0;
}
