#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforoGeneral;

typedef struct {

    sem_t * semaforo [2];
    int numLector;
} envio;


void *funLector (envio * datos) {

    while (1) {

        printf ("[Lector %i] -> Esperando a intentar leer ...\n", datos -> numLector);
        sem_wait (datos -> semaforo [0]);

        printf ("[Lector %i] -> Intentando leer ...\n", datos -> numLector);
        sem_wait (&semaforoGeneral);

        printf ("[lector %i] -> Leyendo ...\n", datos -> numLector);
        sem_wait (datos -> semaforo [1]);

        printf ("[Lector %i] -> Fin de la lectura\n", datos -> numLector);
        sem_post (&semaforoGeneral);
    }
}


int main (int argc, char const *argv[])
{
    int nLectores = atoi (argv [1]), i, error, opcion, lector;
    sem_t semaforo [2 * nLectores];
    pthread_t hilos [nLectores];
    envio datos [nLectores];

    error = sem_init (&semaforoGeneral, 0, atoi (argv [2]));

    if (error != 0) {

        printf ("Error al crear el semaforo general. Cerrando programa ...\n\n");
        return 0;
    }

    for (i = 0; i < 2 * nLectores; i++) {

        error = sem_init (&semaforo [i], 0, 0);

        if (error != 0) {

            printf ("Error al crear el semaforo del lector %i. Cerrando programa ...\n\n", i);
            return 0;
        }
    }

    for (i = 1; i <= nLectores; i++) {

        datos [i - 1].semaforo [0] = &semaforo [i - 1];
        datos [i - 1].semaforo [1] = &semaforo [i + nLectores - 1];
        datos [i - 1].numLector = i;

        error = pthread_create (&hilos [i], NULL, (void *) funLector, &datos[i - 1]);

        if (error != 0) {

            printf ("Error al crear el hilo del lector %i. Cerrando programa ...\n\n", i);
            return 0;
        }
    }


    while (1) {

        sleep (1);
        printf(" 1 - Intentar Leer\n 2 - Finalizar leer\n 3 - Salir\n\n   Elige una opcion: ");
        scanf ("%i", &opcion);
        fflush (stdin);

        switch (opcion) {

            case 1:

                printf ("Introduzca el numero del lector (de 1 a %i): ", nLectores);
                scanf ("%i", &lector);
                fflush (stdin);

                sem_post (&semaforo [lector - 1]);
                break;

            case 2:

                printf ("Introduzca el numero del lector (de 1 a %i): ", nLectores);
                scanf ("%i", &lector);
                fflush (stdin);

                sem_post (&semaforo [lector + nLectores - 1]);
                break;

            case 3:

                printf ("Saliendo del programa ...\n\n");
                return 0;

            default:

                printf ("Seleccion incorrecta. Vuelva a intentarlo\n\n");
        }
    }
}