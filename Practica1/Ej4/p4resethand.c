#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int numR1 = 0;
int numR2 = 0;

void signal_handler(int senal){

	switch(senal){
	  
	  case 10:
	     numR1++;
	     printf("Senal SIGUSR1 capturada. \n");
	     break;
	     
	  case 12:
	    numR2++;
	    printf("Señal SIGUSR2 capturada. \n");
	    break;
	    
	  case 15:
	    printf("Señal SIGTERM\n");
	    printf("Numero de señales SIGUSR1 : %i\n",numR1);
	    printf("Numero de señales SIGUSR2 : %i\n",numR2);
	    exit(0);
	    
	  default:
	    printf("Error");
	    break;
	}   
}

int main (){

	struct sigaction sig;

	sig.sa_handler = signal_handler;
	sig.sa_flags = SA_RESETHAND;  
	
	if(sigaction(10,&sig,NULL) == -1){
	  perror("Error en la señal\n");
	}
	
	if(sigaction(12,&sig,NULL) == -1){
	  perror("Error en la señal\n");
	}
	
	if(sigaction(15,&sig,NULL) == -1){
	  perror("Error en la señal\n");
	}
	
	
	while(1){
	  pause();
	}

	return 0;
}