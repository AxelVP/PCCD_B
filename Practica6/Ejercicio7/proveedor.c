#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define claves 5


struct msgbuf
{
    long mtype;
    int mtext;

}proveedor;


int main(int argc, char const *argv[])
{
    char *material[] = {"Papel y Tabaco", "Tabaco y Fosforos", "Papel y Fosforos"};
    int idCola[4], materialDepositar = 0, i = 0;
    key_t key;

    for(i=0; i<4; i++){

        key = claves + i;
        idCola[i] = msgget(key, IPC_CREAT|0777);
        msgctl(idCola[i], IPC_RMID, NULL);
        idCola[i] = msgget(key, IPC_CREAT|0777);
    }

    proveedor.mtype = 1;
    proveedor.mtext = 0;

    while (1)
    {
        materialDepositar = rand()%3;
        printf("Se coloca en la mesa : %s \n", material[materialDepositar]);
        msgsnd (idCola[materialDepositar], &proveedor, sizeof(int), 0);

        printf("Esperando a que el fumador termine el piti...");
        msgrcv(idCola[3], &proveedor, sizeof(int), 1, 0);

    }
    
    exit(0);
}
