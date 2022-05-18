#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int senal){

    switch(senal){
     
      case SIGUSR1:
	printf("Planta subida \n");
	break;
  
      case SIGUSR2:
	printf("Planta bajada \n");
	break;

      case SIGQUIT:
	printf("Saliendo \n");
	exit(0);
	
      default:
	printf("Error \n");
	break;
    }
	
  
}

void alarma(){
	alarm(T_PISO);
	return 0;
}

int main (){
  
    int i = 0;
    struct sigaction sig;
    sig.sa_handler = signal_handler;
    
    for(i=0; i<64; i++){
	  sigaction(i,&sig,NULL);
    }
    
    while(1){
      pause();
    }
    
    return 0;
}
      
      
