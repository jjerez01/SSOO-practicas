#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>

void copy(char* fdo, char* fdd)
{
	int s;
	char buffer[512];
	
	int or = open(fdo,O_RDONLY,0664);
	int des = open(fdd,O_WRONLY|O_CREAT|O_TRUNC,0664);
	printf("%d\n",or);
	printf("%d\n",des);
	while(s = read(or,buffer,512) == 512){
		write(des,buffer,512);
	}

	close(or);
	close(des);
}

int main(int argc, char *argv[])
{
	
	char* fdo = argv[1];
	char* fdd = argv[2];
	copy(fdo,fdd);
	return 0;
}
