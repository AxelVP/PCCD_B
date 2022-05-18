#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char const *argv[])
{
    int id = 0;

    key_t key = ftok("/home/axel/Escritorio/CLASE/3º/2cuatri/PCCD/Practica/Practica6", 1); //Convierte una direccion en una clave IPC

    if(key == -1){
        printf("Error al crear la clave para el msgget \n");
        exit(0);
    }    

    id = msgget(key,IPC_CREAT|0777);

    if(id == -1){
        printf("Error al crear la cola de mensajes \n");
        exit(0);
    }

    printf("Exito al crear la cola con ID : %i \n",id);

    return 0;
}
