#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int X[64] = {0};

void signal_handler(int senal){

	int i;

	printf("Senal %i detectada \n",senal);
	X[senal] = 1;

	if(senal==15){
		printf("Recibida la señal SIGTERM...\n");
		exit(0);
	}
}

int main (){

	struct sigaction sig;

	sig.sa_handler = signal_handler;
	int i = 0;

	for(i=0; i<64; i++){
		sigaction(i,&sig,NULL);
	}
	while(1){
		pause();
	}

	return 0;
}
