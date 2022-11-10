#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* programa que crea N hijos siguiendo un grado de dependencias. Usa las
 * versiones de execl y execlp */


/*int main(int argc, char **argv)
{
	int wstatus;
	int w;

	int pid1 = fork();
	if(pid1 == 0){
		printf("soy proceso 1");
		exit(1);
	}else{
		do {
					w = waitpid(pid1, &wstatus, WUNTRACED | WCONTINUED);
					if (w == -1) {
						perror("waitpid");
						exit(EXIT_FAILURE);
					}

					if (WIFEXITED(wstatus)) {
						printf("exited, status=%d\n", WEXITSTATUS(wstatus));
					} else if (WIFSIGNALED(wstatus)) {
						printf("killed by signal %d\n", WTERMSIG(wstatus));
					} else if (WIFSTOPPED(wstatus)) {
						printf("stopped by signal %d\n", WSTOPSIG(wstatus));
					} else if (WIFCONTINUED(wstatus)) {
						printf("continued\n");
					}
				} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}

	int pid2 = fork();
	if(pid2 == 0){
		printf("soy proceso 2");
		exit(1);
	}else{

		int pid5 = fork();
		if(pid5 == 0){
			printf("soy proceso 5");
			
		}else{
			
			int pid7 = fork();
			if(pid7 == 0){
				printf("soy proceso 7");
			}
					
		}

		do {
					w = waitpid(pid2, &wstatus, WUNTRACED | WCONTINUED);
					if (w == -1) {
						perror("waitpid");
						exit(EXIT_FAILURE);
					}

					if (WIFEXITED(wstatus)) {
						printf("exited, status=%d\n", WEXITSTATUS(wstatus));
					} else if (WIFSIGNALED(wstatus)) {
						printf("killed by signal %d\n", WTERMSIG(wstatus));
					} else if (WIFSTOPPED(wstatus)) {
						printf("stopped by signal %d\n", WSTOPSIG(wstatus));
					} else if (WIFCONTINUED(wstatus)) {
						printf("continued\n");
					}
				} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}			

	int pid3 = fork();
	if(pid3 == 0){
		printf("soy proceso 3");
		
	}else{
		int pid4 = fork();
		if(pid4 == 0){
			printf("soy proceso 4");
			
		}else{
		do {
				w = waitpid(pid5, &wstatus, WUNTRACED | WCONTINUED);
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(wstatus)) {
					printf("exited, status=%d\n", WEXITSTATUS(wstatus));
				} else if (WIFSIGNALED(wstatus)) {
					printf("killed by signal %d\n", WTERMSIG(wstatus));
				} else if (WIFSTOPPED(wstatus)) {
					printf("stopped by signal %d\n", WSTOPSIG(wstatus));
				} else if (WIFCONTINUED(wstatus)) {
					printf("continued\n");
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		}

		int pid6 = fork();
		if(pid6 == 0){
			printf("soy proceso 6");

		}


		

	}
	return 0;
}*/

int main(int argc, char **argv)
{
	int wstatus;
	int w;

	int pid1 = fork();
	if(pid1 == 0){
		printf("soy proceso 1");
		exit(1);
	}else{
		do {
					w = waitpid(pid1, &wstatus, WUNTRACED | WCONTINUED);
					if (w == -1) {
						perror("waitpid");
						exit(EXIT_FAILURE);
					}

					if (WIFEXITED(wstatus)) {
						printf("exited, status=%d\n", WEXITSTATUS(wstatus));
					} else if (WIFSIGNALED(wstatus)) {
						printf("killed by signal %d\n", WTERMSIG(wstatus));
					} else if (WIFSTOPPED(wstatus)) {
						printf("stopped by signal %d\n", WSTOPSIG(wstatus));
					} else if (WIFCONTINUED(wstatus)) {
						printf("continued\n");
					}
				} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}

	int pid2 = fork();
	if(pid2 == 0){
		printf("soy proceso 2");

	}

	int pid5 = fork();
	if(pid5 == 0){
		printf("soy proceso 5");
		
	}
			
	int pid7 = fork();
	if(pid7 == 0){
		printf("soy proceso 7");
	}
				
	do {
				w = waitpid(pid2, &wstatus, WUNTRACED | WCONTINUED);
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(wstatus)) {
					printf("exited, status=%d\n", WEXITSTATUS(wstatus));
				} else if (WIFSIGNALED(wstatus)) {
					printf("killed by signal %d\n", WTERMSIG(wstatus));
				} else if (WIFSTOPPED(wstatus)) {
					printf("stopped by signal %d\n", WSTOPSIG(wstatus));
				} else if (WIFCONTINUED(wstatus)) {
					printf("continued\n");
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
			

	int pid3 = fork();
	if(pid3 == 0){
		printf("soy proceso 3");
		
	}
	int pid4 = fork();
	if(pid4 == 0){
		printf("soy proceso 4");
		
	}
		
	do {
			w = waitpid(pid5, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	

	do {
			w = waitpid(pid4, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	

	int pid6 = fork();
	if(pid6 == 0){
		printf("soy proceso 6");

	}

	do {
			w = waitpid(pid7, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	do {
			w = waitpid(pid3, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	do {
			w = waitpid(pid6, &wstatus, WUNTRACED | WCONTINUED);
			if (w == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			}

			if (WIFEXITED(wstatus)) {
				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
			} else if (WIFSIGNALED(wstatus)) {
				printf("killed by signal %d\n", WTERMSIG(wstatus));
			} else if (WIFSTOPPED(wstatus)) {
				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
			} else if (WIFCONTINUED(wstatus)) {
				printf("continued\n");
			}
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		
	int pid8 = fork();
	if(pid8 == 0){
		printf("soy proceso 6");

	}else{
		do {
				w = waitpid(pid8, &wstatus, WUNTRACED | WCONTINUED);
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(wstatus)) {
					printf("exited, status=%d\n", WEXITSTATUS(wstatus));
				} else if (WIFSIGNALED(wstatus)) {
					printf("killed by signal %d\n", WTERMSIG(wstatus));
				} else if (WIFSTOPPED(wstatus)) {
					printf("stopped by signal %d\n", WSTOPSIG(wstatus));
				} else if (WIFCONTINUED(wstatus)) {
					printf("continued\n");
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	}
	
	return 0;
}

