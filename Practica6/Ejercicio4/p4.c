#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf
{
    long mtype;
    char *mtext;
}mensaje;

int main(int argc, char const *argv[])
{
    int control = 0, tamano = 0;

    if(argc != 2){
        printf("Faltan parametros \n");
        exit(0);
    }

    int id = atoi(argv[1]);

    mensaje mensaje;
    mensaje.mtype = 1;
    tamano = sizeof(mensaje.mtext);

    control = msgrcv(id, &mensaje, tamano, 0, 0);

    if(control == -1){
        printf("Error al recibir el mensaje, saliendo... \n");
        exit(0);
    }
    printf("Mensaje recibido correctamente desde la cola con id : %i \n", id);


    return 0;
}
