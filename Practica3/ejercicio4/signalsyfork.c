#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


/*
este es un programa que temporiza la ejecución de un proceso hijo

para ello usaremos señales y adicionalmente diremos si el programa 
ha terminado por culpa de una señal o no. 
*/

/*
para este tipo de ejercicios que requieren del uso de señales tendremos que 
crear un handler para poder cortar al proceso en caso de que reciba una señal 
especifica

en este ejemplo la señal que el proceso recibira sera una señal para matar el proceso
*/
pid_t pid;
void handler(int signal){
	/*
	esta señal es enviada para matar al proceso hijo en caso de que supere los 5 segundos
	que pondremos de alarma
	*/
	kill(pid,SIGKILL);
}

int main(int argc, char **argv)
{
	struct sigaction act;
	int status;
	pid = fork();
	if(pid == 0){
		printf("soy el proceso hijo\n");
		/*
		execvp(nombre del comando, char* como de como tienen que ir los
									argumentos del comando)
		*/
		execvp(argv[1], &argv[1]);
		perror("execvp");
      	exit(1);
	}
	/*
	IMPORTANTE: para este tipo de ejercicios tenemos que hacer siempre una funcion
	handler para despues poder pasar a act.sa_handler UN PUNTERO A FUNCION (tal y como esta abajo)
	*/
	act.sa_handler = handler;
	act.sa_flags = SA_RESTART; 
    sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);

	//programamos la alarma
    alarm(5);
	
	/*
	aqui el padre espera a que acabe el hijo de ejecutar el programa pidiendo la variable status
	que servira para despues ver como ha acabado el proceso
	*/
	wait(&status);
	printf("soy el proceso padre\n");

	/*
	como en el ejercicio nos dicen que miremos si el programa acaba de forma natural o viendo si han matado
	al proceso, para ver que ha pasado usamos la flag de wait WIFSIGNALED(status) para ver si ha terminado 
	POR UNA SEÑAL o no
	*/
	if (WIFSIGNALED(status)) {
        printf("El proceso hijo ha finalizado por recepción de una señal\n");
    } else {
        printf("El proceso hijo ha finalizado de forma normal\n");
    }

	return 0;
}

