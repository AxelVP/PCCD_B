#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgbuf
{
    long mtype;
    int numeroTenedor;

}Tenedor[5];

int main(int argc, char const *argv[])
{
    
    int id = atoi(argv[1]), i=0, control = 0, tamano = 0;

    for(i=1; i<=5; i++){

        Tenedor[i].mtype = i;
        Tenedor[i].numeroTenedor = i;

        tamano = sizeof(Tenedor[i].numeroTenedor);

        control = msgsnd(id, &Tenedor[i], tamano, IPC_NOWAIT);

        if(control == -1){
            printf("Error al enviar el tenedor, saliendo... \n");
            exit(0);
        }
        printf("Tenedor enviado correctamente a la cola con id : %i \n", id);
        
    }

    printf("Terminado el inic_filosofos... \n");

    return 0;
}


