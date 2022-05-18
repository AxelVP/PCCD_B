#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("Faltan parametros \n");
        exit(0);
    }

    int id = atoi(argv[1]);
    int control = 0;

    control = msgctl(id,IPC_RMID, NULL);

    if(control == -1){
        printf("Error al eliminar la cola, saliendo... \n");
        exit(0);
    }

    printf("La cola con id = %i fue eliminada correctamente \n", id);

    return 0;
}



