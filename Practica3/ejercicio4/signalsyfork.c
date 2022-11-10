#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


/*programa que temporiza la ejecución de un proceso hijo */


int main(int argc, char **argv)
{
	struct sigaction act;

	int pid = fork();

	if(pid ==0){
		printf("soy el proceso hijo\n");
		char* argument_list[] = {"ls", "-l", NULL};
		execvp("ls", argument_list);
		perror("exec");
      	exit(1);

	}
	act.sa_handler = kill(pid, SIGKILL);
	act.sa_flags = 0; /* ninguna accion especifica */
      sigemptyset(&act.sa_mask);
	wait(pid);
	printf("soy el proceso padre\n");

	return 0;
}
