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
    key_t clave = ftok ("meQuieroMorir", 's');
    int zonaMemoria = -1;
    zonaMem * memoria;

    zonaMemoria = shmget (clave, sizeof (zonaMem), 0);
    memoria = shmat (zonaMemoria, NULL, 0);

    printf ("El numero guardado en la zona de memoria es un %i\n\n", memoria -> numero);

    return 0;
}
