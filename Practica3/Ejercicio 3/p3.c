#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

typedef struct
{
    int numero;
} zonaMem;

int main(int argc, char const *argv[])
{
    int zonaMemoria = -1, error;

    key_t clave = ftok("meQuieroMorir", 's');
    zonaMemoria = shmget(clave, sizeof (zonaMem), 0);

    error = shmctl (zonaMemoria, IPC_RMID, NULL);

    if (error == -1) {

        printf ("Error al cerrar el segmento compartido\n\n");
    }

    return 0;
}
