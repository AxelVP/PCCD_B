#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

	int num_senal = atoi(argv[1]);
	int pID =  atoi(argv[2]);

	kill(num_senal,pID);
	return 0;
} 
