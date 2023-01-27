#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define M 5

int main(int argc, char *argv[])
{
	int ofile;
	int has_e = 0;
	
	if(argc == 1){
		perror("necesitas 2 argumento");
		exit(1);
	}

	int opt,N;
	/*
		getopt lo que va a hacer es pasar todo el rato por los argumentos intentando encontrar la letra correspondiente

		(por lo que primero lee la -n y luego como es un bucle podria leer la -e)

		varias cosas:
		1. acordarse que al poner en getopt "n:" puedes usar optarg para coger la siguiente string (en este caso el numero 
		que puedes transformar a int con atoi(N)) 

		2. en este caso cuando tienes que leer el fichero de despues, como el get opt se para al no haber mas letras, optind es la variable que te
		almacena el indice del siguiente argumento (en este caso el fichero) y con ello puedes poner argv[optind] para coger 
	*/
	while((opt = getopt(argc,argv,"n:e")) != -1){
		switch(opt){
			case 'n':
			N = atoi(optarg);

			break;
			case 'e':
			has_e = 1;
			break;
		}
	}



	ofile = open(argv[optind],O_RDWR,0660 ); 
	/* para hacer lseek (que es una llamada al sistema) habria que abrir el archivo con open en vez de fopen*/
	if(ofile == -1){
		exit(1);
	}
	printf("se ha abierto el archivo\n");

	if(has_e){
		lseek(ofile,-N,SEEK_END);
	}else{
		lseek(ofile,N,SEEK_SET);
	}
	printf("se ha hecho el lseek\n");

	/*
	para esta parte del ejercicio lo que te piden es leer byte a byte hasta imprimir lo que te salgasin embargo yo 
	lo voy a complicar un poco mas para practicar y voy a leer de 5 en 5 bytes.

	para ello usamos la funcion read(nombre del archivo,buffer en el que vas a poner lo leido, tamaño en bytes de lo que vas a leer)

	como podemos ver abajo, creamos el buffer de tamaño M y luego ponemos despues M para que lea M bytes

	la funcion read(...) devuelve el numero de bytes que ha leido asi que si no lee ninguno pues acaba
	(hay veces que se comporta de forma extraña asi que si quieres hacer que pare de leer antes y tal puedes hacer 
	read(ofile,buffer,M) == 5 o puedes jugar con esta condicion como quieras...) 

	*/
	char buffer[M];
	while(read(ofile,buffer,M) != 0){
		printf("%s",buffer); //imprime los M bytes
	}
	

	return 0;
}