#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


int main (int numArgs, char *args[]){

	int pid = atoi(args[1]);
	
	int opcion = 0;
	printf("Pulsador : \n");
	
	while(1){
	  
	  printf("1) Subir\n");
	  printf("2) Bajar\n");
	  printf("3) Salir\n");
	  
	  scanf("%i",&opcion);
	
	
	switch(opcion){
	  
	  case 1:
	    if(kill(pid,10) < 0){
	      printf("Fallo al intentar subir \n");
	      exit(0);
	    }
	    printf("Opcion : Subir \n");
	    break;
	  
	  case 2:
	    if(kill(pid,12) < 0){
	      printf("Fallo al intentar bajar \n");
	      exit(0);
	    }
	    printf("Opcion : Bajar \n");
	    break;
	  
	  case 3:
	    if(kill(pid,3) < 0){
	      printf("Fallo al intentar salir \n");
	      exit(0);
	    }
	    printf("Saliendo \n");
	    exit(0);
	  
	  default:
	    printf("Error en la opcion\n");
	    break;
	}
    }
}