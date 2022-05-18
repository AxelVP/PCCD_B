/*
    NOTAS DE LA MEMORIA COMPARTIDA PUTA MADRE

    shmget (key, size, flags): devuelve el identificador del segmento de memoria compartida asociado a una clave key

        - key es la "clave" que utilizas para acceder al segmento de memoria compartida
        - size es el tamaño del segmento de memoria redondeando hacia arriba a un multiplo del tamaño de pagina
        - flags hacen cosas varias


    shmat (shmid, *shmaddr, flags)

        - shmmid es el ID de la zona de memoria compartida a la que va a ir el procesador a buscar cosas
        - shmaddr hace cosas dependiendo de lo que valga:
            + Si es nulo, el segmento se mete en la primera seccion de memoria disponible que pille
            + Si no es nulo y el flag es SHM_RND, se mete en la direccion de memoria = shmaddr redondeada
            + En cualquier otro caso, se mete en la direccion de memoria que ponga shmaddr (violacion de segmento asegurada papu)


    shmdt (*shmaddr)
    
        - shmaddr te dice la zona de memoria que desenchufas del proceso 

*/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

typedef struct
{
    int numero;
} zonaMem;

int main (int argc, char const *argv[])
{
    int zonaMemoria = -1, argumento = atoi (argv [1]);
    zonaMem * memoria;
    key_t clave = ftok ("meQuieroMorir", 's');
    zonaMemoria = shmget (clave, sizeof(zonaMem), IPC_CREAT | 0660);

    memoria = shmat (zonaMemoria, NULL, 0);
    memoria -> numero = argumento;

    printf ("La zona de memoria es %i (%i guardado)\n\n", zonaMemoria, memoria -> numero);

    return 0;
}
