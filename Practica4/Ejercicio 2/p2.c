#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {

    char* texto;
    int posicion;

}informacion;


void *hagocosas(informacion *arg){

    printf("Posicion: %i Texto: %s \n",arg -> posicion, arg -> texto);

    //pthread_exit(NULL);
    return 0;
}


int main(int argc, char *argv[]){

    pthread_t idHilo[argc-1];
    informacion parametros[argc -1];

    int error = 0;
    int i = 0;
    for(i=1; i<argc; i++){

        parametros[i].texto = argv[i];
        parametros[i].posicion = i;


        error = pthread_create(&idHilo[i],NULL,(void *)hagocosas,&parametros[i]);

        if(error!=0){
            printf("Ha habido un error en la creacion del hilo %i ",i);
        }

    }
    pthread_exit(NULL);

    return 0;
}
