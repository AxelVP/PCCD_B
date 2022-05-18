#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int pisoActual = 0;
int numMaxPisos = 0;
int subidas = 0;
int bajadas = 0;
int T_PISO = 3;

void signal_handler(int senal){

	switch(senal){
	  
	  case 10: /************Sube***********/
	    
	    if(pisoActual == numMaxPisos){
	      printf("Ultimo piso alcanzado, imposible subir mas \n");
	    }else{
	      printf("Subiendo\n");
	      subidas++;
	      pisoActual++;
	      sleep(T_PISO);
	      printf("Piso : %i \n", pisoActual);
	    }
	    break;
	     
	  case 12: /************Baja************/
	    
	    if(pisoActual == 0){
	      printf("Piso 0 alcanzado, no se puede bajar mas \n");
	    }else{
	      printf("Bajando\n");
	      bajadas++;
	      pisoActual = pisoActual-1;
	      sleep(T_PISO);
	      printf("Piso : %i \n", pisoActual);
	    }
	    break;
	 
	    
	  case SIGQUIT: /***********Termina**********/
	    printf("Fin del proceso\n");
	    printf("Numero de subidas : %i\n",subidas);
	    printf("Numero de bajadas : %i\n",bajadas);
	    exit(0);
	    
	  default:
	    printf("Error");
	    break;
	}   
}

int main (int numArgs, char *args[]){

	struct sigaction sig;
	int i = 0;
	
	if(numArgs !=2){
	  printf("Error en los argumentos \n");
	  return 0;
	}
	
	numMaxPisos = atoi(args[1]);

	sig.sa_handler = signal_handler;
	
	for(i=0; i<64; i++){
	  sigaction(i,&sig,NULL);
	}
	
	
	while(1){
	  pause();
	}

	return 0;
}