#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 

char fname[] = "argXX";

int write_args(int i)
{
    FILE* f;
    snprintf(fname, sizeof(fname),
    "arg%02d", i);
    f = fopen(fname, "w");
    fprintf(f,
    "my pid is %lld and my arg is: %d\n",
    (long long int) getpid(), i + 1000);
    fclose(f);
}

int main(int argc, char *argv[])
{
    int i,pid,n;
    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            write_args(i);
            execlp("cat", "cat",fname, NULL);
            exit(EXIT_FAILURE);
        }
    }
    while (wait(NULL) > 0);
    exit(EXIT_SUCCESS);
}