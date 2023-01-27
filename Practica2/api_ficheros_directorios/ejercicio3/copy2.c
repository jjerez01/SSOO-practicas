#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
		#include <sys/stat.h>
		#include <fcntl.h>
#include <unistd.h>

#define TAM 1

struct stat s;

void copy(int fdo, int fdd)
{

}

void copy_regular(char *orig, char *dest)
{
	int leido;
	char buffer[TAM];
	int o = open(orig,O_RDONLY,0664);
	int d = open(dest,O_WRONLY | O_CREAT | O_TRUNC,0664);

	while((leido = read(o,buffer,TAM))==TAM){
		if (write( d,buffer, TAM) < TAM)  {
			perror("write");
			close(o); 
			close(d);
			exit(-1);
       	}

	}
	close(o); 
	close(d);

}

void copy_link(char *orig, char *dest)
{	
	char *path = malloc(s.st_size +1);

	readlink(orig,path,s.st_size+1);
	path[s.st_size] = 0;
	symlink(path,dest);
	
	free(path);

}

int main(int argc, char *argv[])
{
	if (lstat(argv[1], &s) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

	if((s.st_mode & S_IFMT) == __S_IFREG){
		copy_regular(argv[1],argv[2]);
	}
	else if((s.st_mode & S_IFMT) == S_IFLNK){
		copy_link(argv[1],argv[2]);
	}
	else{
		printf("error fichero no esperado");
		exit(EXIT_FAILURE);
	}
	return 0;
}
