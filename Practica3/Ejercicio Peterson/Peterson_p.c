#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

typedef struct
{
    int ultimo;
    int quiereP;
    int quiereQ;
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
    memoria -> quiereP = 0;

    while (1)
    {
        printf ("Caminando por mi habitacion");

        while (getchar () != '\n');
        printf ("Dentro del pasillo");

        while (getchar () != '\n');
        printf ("He accionado el pulsador");
        memoria -> ultimo = 0;
        memoria -> quiereP = 1;

        while (getchar() != '\n'); 
        printf ("Intentando acceder a la Seccion Critica ...\n");
            
        if (memoria -> quiereQ == 0 || (memoria -> quiereQ ==1 && memoria -> ultimo == 1)) {

            printf ("Dentro de mi Seccion Critica");

            while (getchar () != '\n');
            printf ("He salido de mi Seccion Critica");

            while (getchar () != '\n');
            printf ("He accionado el pulsador\n\n");
            memoria -> quiereP = 0;

        } else {

            printf ("Puerta Cerrada. Saliendo del pasillo ...");

            while (getchar () != '\n');
            printf ("He accionado el pulsador\n");
            memoria -> quiereP = 0;

            printf ("He salido al pasillo\n\n");
        }
    }

    return 0;
}
