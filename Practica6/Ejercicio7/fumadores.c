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

}fumadores;

int main(int argc, char const *argv[])
{
    
    int idCola[4], i=0;
    int fumador = atoi(argv[1]);
    char *materialDispone;
    key_t key;

    for(i=0; i<4; i++){

        key = claves + i;
        idCola[i] = msgget(key, IPC_CREAT|0777);

    }

    fumadores.mtype = 1;
    fumadores.mtext = 1;

    switch (fumador)
    {
    case 0:     
        materialDispone = "Fosforo";
        break;
    
    case 1:
        materialDispone = "Papel";
        break;
    
    case 2:
        materialDispone = "Tabaco";
        break;
    
    default:
        printf("Fumador no contemplado, introduzca uno valido (0, 1, 2)... \n");
        exit(0);
    }


    while (1)
    {
        printf("Fumador %i con material %s intenta fumar \n", fumador, materialDispone);
        msgrcv(idCola[fumador], &fumadores, sizeof(int), 1, 0);

        printf("El fumador %i ha cogido los materiales y fuma \n", fumador);
        getchar();

        msgsnd(idCola[3], &fumadores, sizeof(int), 0);
        printf("El fumador %i deja de fumar \n", fumador);
    }
    

    exit(0);
}
