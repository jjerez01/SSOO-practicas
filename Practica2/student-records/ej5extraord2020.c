#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZEBUF 10
int rd_idx=0;
int wr_idx=0;
int buffer[SIZEBUF];
/* Semaphore definitions */


void producer1(){

    int i=0;
    
    for(i=0;i<20;i++){
        int item=generate_random_num();

        /* Insertion */
        buffer[wr_idx]=item;
        wr_idx=(wr_idx+1)%SIZEBUF;

    }
}

void producer2(){
    int i=0;
    for(i=0;i<40;i++){
        int item=generate_random_num();

        /* Insertion */
        buffer[wr_idx]=item;
        wr_idx=(wr_idx+1)%SIZEBUF;
    }
}

void consumer(){
    int i=0;

    for(i=0;i<60;i++){
        /* Removal */
        int item=buffer[rd_idx];
        rd_idx=(rd_idx+1)%SIZEBUF;

        do_something_with(item);
    }
}