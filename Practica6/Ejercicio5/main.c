#include <stdio.h>  //        1 : Izquierda = 1, Derecha = 5               
#include <stdlib.h> //        2 : Izquierda = 2, Derecha = 1     
#include <sys/types.h>//      3 : Izquierda = 3, Derecha = 2
#include <sys/ipc.h>//        4 : Izquierda = 4, Derecha = 3                    
#include <sys/msg.h>//        5 : Izquierda = 5, Derecha = 4
#include <unistd.h>

struct msgbuf
{
    long mtype;             //tipo de mensaje que debe ser > 0
    int numeroTenedor;      //datos que va a contener el mensaje

}Tenedor[5];


void comer(int id, int num_filosofo){

    int num_tenedor_derecha = num_filosofo -1;

    if(num_tenedor_derecha == 0){
        num_tenedor_derecha = 5;
    }

    printf("El filosofo %i intenta coger el tenedor. \n", num_filosofo);

    msgrcv(id, &Tenedor[num_filosofo], sizeof(int), num_filosofo, 0);

    printf("El filosofo %i ha cogido el tenedor %i : Primer tenedor \n", num_filosofo, num_filosofo);


    printf("Procede a coger el segundo tenedor. \n");

    msgrcv(id, &Tenedor[num_tenedor_derecha], sizeof(int), num_tenedor_derecha, 0);

    printf("El filosofo %i ha cogido el tenedor %i : Segundo tenedor \n", num_filosofo, num_tenedor_derecha);

    printf("El filosofo %i procede a comer. \n", num_filosofo);

    sleep(5);

    printf("El filosofo %i termino de comer y deja los tenedores. \n\n", num_filosofo);

    Tenedor[num_filosofo].mtype = num_filosofo;
    Tenedor[num_filosofo].numeroTenedor = num_filosofo;

Tenedor[num_tenedor_derecha].mtype = num_tenedor_derecha;
    Tenedor[num_tenedor_derecha].numeroTenedor = num_tenedor_derecha;

    msgsnd(id, &Tenedor[num_filosofo], sizeof(int), IPC_NOWAIT);
    msgsnd(id, &Tenedor[num_tenedor_derecha], sizeof(int), IPC_NOWAIT);

    return;

}

int main(int argc, char const *argv[])
{
    
    int num_filosofo = 0, id = atoi(argv[1]), opcion = 0;

    do
    {
        printf("1. Seleccione un filosofo para que coma. \n");
        printf("2. Salir de la aplicacion. \n");

        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Introduzca el numero del filosofo (1-5) : \n");
            scanf("%i", &num_filosofo);
            comer(id, num_filosofo);
            break;
        
        case 2: 
            printf("Saliendo... \n");
            exit(0);

        default:
            printf("Opcion no contemplada. \n");
            break;
        }
    } while (1);
    

    return 0;
}
