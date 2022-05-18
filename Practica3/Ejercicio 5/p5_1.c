#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

typedef struct
{
    int turno;
} zonaMem;


int main (int argc, char const *argv[])
{
    int zonaMemoria = -1;
    zonaMem *memoria;
    key_t clave = ftok ("meQuieroMorir", 's');
    zonaMemoria = shmget (clave, sizeof (zonaMem), IPC_CREAT | 0660);

    if (zonaMemoria == -1) {

        zonaMemoria = shmget (clave, sizeof (zonaMem), 0);
    }

    memoria = shmat (zonaMemoria, NULL, 0);
    memoria -> turno = 1;

    while (1)
    {
        printf ("Caminando por mi habitacion");

        while (getchar () != '\n');

        printf ("Intentando entrar en mi seccion critica ...");
        
        if (memoria -> turno == 1) {

            printf ("Dentro de mi Seccion Critica");
            while (getchar () != '\n');

            printf ("He salido de mi Seccion Critica");
            while (getchar () != '\n');

            printf ("He accionado el pulsador\n\n");
            memoria -> turno = 0;

        } else {

            printf ("Puerta Cerrada\n\n");
        }

    }

    return 0;
}
