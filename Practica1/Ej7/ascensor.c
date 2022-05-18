#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int pisoActual = 0;
int numMaxPisos = 0;
int subidas = 0;
int bajadas = 0;
int T_PISO = 3;
int llego = 0;

void signal_handler(int senal){

	switch(senal){
	  
	  case 10: /************Sube***********/
	    
	    if(pisoActual != numMaxPisos){
			subidas++;
	      	pisoActual++;
	    }
	    break;
	     
	  case 12: /************Baja************/
	    
	    if(pisoActual == 0){
	      printf("Piso 0 alcanzado, no se puede bajar mas \n");
	    }else{
	      printf("Bajando\n");
	      bajadas++;
	      pisoActual = pisoActual-1;
	      printf("Piso : %i \n", pisoActual);
	    }
	    break;
	 
	    
	  case SIGQUIT: /***********Termina**********/
	    printf("Fin del proceso\n");
	    printf("Numero de subidas : %i\n",subidas);
	    printf("Numero de bajadas : %i\n",bajadas);
	    exit(0);

		case 14:
			printf("Esperando a que llegue el ascensor\n");
			llego=1;
			break;
	    
	  default:
	    printf("Error");
	    break;
	}   
}

int main (int numArgs, char *args[]){

	struct sigaction sig;
	int i = 0;

	
	numMaxPisos = atoi(args[1]);
	
	int pidSensor = atoi(args[2]);

	sig.sa_handler = signal_handler;
	
	for(i=1; i<=64; i++){
	  sigaction(i,&sig,NULL);
	  
	  if(sigaction(10,&sig,NULL) != -1){	  
	    kill(pidSensor, 10);	    
	  }
	  
	  if(sigaction(12,&sig,NULL) != -1){	  
	    kill(pidSensor, 12);	    
	  }
	  
	  if(sigaction(3,&sig,NULL) != -1){	  
	    kill(pidSensor, 3);	    
	  }
	  
	}
	llego = 0;
	
	while(llego==0){
	  alarm(T_PISO);
	}

	return 0;
}
