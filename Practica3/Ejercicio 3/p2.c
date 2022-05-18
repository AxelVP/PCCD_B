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
    char salida;

    zonaMemoria = shmget (clave, sizeof (zonaMem), 0);

    do
    {
        fflush;
        memoria = shmat (zonaMemoria, NULL, 0);

        printf ("El numero guardado en la zona de memoria es un %i\n\n", memoria -> numero);
        salida = getchar ();

    } while (salida != 'q');

    return 0;
}
