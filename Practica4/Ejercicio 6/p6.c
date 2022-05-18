#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


int escribiendo = 0, leer = 0;

int num_lectores_leyendo = 0, num_lectores_queriendo_leer = 0, esperando_escribir = 0;

sem_t semaforoMaxLectores, semaforoEscritores, semaforoGlobal;

typedef struct {
    sem_t *semaforo[2];
    int id;
} envio;


void *funLector (envio *datos) {

    while (1)
    {

        printf ("[Lector %i] -> Esperando a intentar leer ...\n", datos->id);
        sem_wait (datos->semaforo[0]);

        printf ("[Lector %i] -> Intentando leer ...\n", datos->id);
        sem_wait (&semaforoGlobal);
        leer++;
        num_lectores_queriendo_leer++;
        
        if(leer == 1){
            if(escribiendo !=0) {
                sem_wait(&semaforoGlobal);
            }else{
                sem_wait(&semaforoEscritores);
                sem_post(&semaforoGlobal);
            }
        }else{
            if(num_lectores_queriendo_leer != 0){
                sem_post(&semaforoMaxLectores);
            }
            sem_post(&semaforoGlobal);
        }
        
        //sem_wait(&semaforoMaxLectores);

        printf ("[lector %i] -> Leyendo ...\n", datos->id);
        sem_wait (datos->semaforo[1]);

        printf ("[Lector %i] -> Fin de la lectura\n", datos->id);
        sem_post (&semaforoMaxLectores);
        sem_wait(&semaforoGlobal);

        leer--;

        if(leer == 0){
            sem_post(&semaforoEscritores);

            sem_post(&semaforoGlobal);
        }else{
            sem_post(&semaforoGlobal);
        }
    }
}


void *funEscritor (envio *datos) {

    while (1)
    {

        printf ("[Escritor %i] -> Esperando a intentar escribir ...\n", datos->id);
        sem_wait (datos->semaforo[0]);

        printf ("[Escritor %i] -> Intentando escribir ...\n", datos->id);
        escribiendo ++;
        sem_wait (&semaforoEscritores);

        printf ("[Escritor %i] -> Escribiendo ...\n", datos->id);
        sem_wait (datos->semaforo[1]);

        printf ("[Escritor %i] -> Fin de la lectura\n", datos->id);
        escribiendo --;

        if(escribiendo == 0) {
            if(leer != 0){
                sem_post(&semaforoEscritores);
                sem_post (&semaforoGlobal);
            }else{
                sem_post(&semaforoEscritores);
            }
        }else {
            sem_post(&semaforoEscritores);
        }
    }
}




int main(int argc, char const *argv[])
{
    
    int nLectores = atoi (argv [1]), nEscritores = atoi (argv [3]), error, i, opcion, id;
    sem_t semaforoLec [2 * nLectores], semaforoEsc [2 * nEscritores];
    pthread_t hilosLectores [nLectores], hilosEscritores [nEscritores];
    envio datosLectores [nLectores], datosEscritores [nEscritores];
    
    error = sem_init (&semaforoEscritores, 0, 1);

    if (error != 0) {

        printf ("Error al crear el semaforo de los escritores. Cerrando programa ...\n\n");
        return 0;
    }

    error = sem_init (&semaforoMaxLectores, 0, atoi (argv [2]));

    if (error != 0)
    {

        printf ("Error al crear el semaforo de los lectores. Cerrando programa ...\n\n");
        return 0;
    }

    for (i = 0; i < 2 * nLectores; i++) {

        error = sem_init (&semaforoLec [i], 0, 0);

        if (error != 0) {

            printf ("Error al crear el semaforo del lector %i. Cerando programa ...\n\n", i);
            return 0;
        }
    }

    for (i = 0; i < 2 * nEscritores; i++) {

        error = sem_init (&semaforoEsc [i], 0, 0);

        if (error != 0) {

            printf ("Error al crear el semaforo del escritor %i. Cerrando programa ...\n\n", i);
            return 0;
        }
    }

    sem_init(&semaforoGlobal,1,1);

    for (i = 0; i < nLectores; i++) {

        datosLectores [i]. id = i + 1;
        datosLectores [i]. semaforo [0] = &semaforoLec [i];
        datosLectores [i]. semaforo [1] = &semaforoLec [i + nLectores];
    
        error = pthread_create (&hilosLectores [i], NULL, (void *) funLector, &datosLectores [i]);

        if (error != 0) {

            printf ("Error al crear el lector %i. Cerrando programa ...\n\n", i + 1);
            return 0;
        }
    }

    for (i = 0; i < nEscritores; i++) {

        datosEscritores [i]. id = i + 1;
        datosEscritores [i]. semaforo [0] = &semaforoEsc [i];
        datosEscritores [i]. semaforo [1] = &semaforoEsc [i + nEscritores];

        error = pthread_create (&hilosEscritores [i], NULL, (void *) funEscritor, &datosEscritores [i]);

        if (error != 0) {

            printf ("Error al crear el lector %i. Cerrando programa ...\n\n", i + 1);
            return 0;
        }
    }

    while (1) {

        sleep (1);

        printf (" 1 - Intentar Leer\n 2 - Finalizar leer\n 3 - Intentar escribir\n 4 - Finalizar escribir\n 5 - Salir\n\n   Elige una opcion: ");
        scanf ("%i", &opcion);
        fflush (stdin);

        switch (opcion) {

            case 1:
                printf ("Introduzca el numero del lector (de 1 a %i): ", nLectores);
                scanf ("%i", &id);
                fflush (stdin);

                sem_post (&semaforoLec [id - 1]);
                break;

            case 2:

                printf ("Introduzca el numero del lector (de 1 a %i): ", nLectores);
                scanf ("%i", &id);
                fflush (stdin);

                sem_post (&semaforoLec [id + nLectores - 1]);
                break;

            case 3:

                printf ("Introduzca el numero del escritor (de 1 a %i): ", nEscritores);
                scanf ("%i", &id);
                fflush (stdin);

                sem_post (&semaforoEsc [id - 1]);
                break;

            case 4:

                printf ("Introduzca el numero del escritor (de 1 a %i): ", nEscritores);
                scanf ("%i", &id);
                fflush (stdin);

                sem_post (&semaforoEsc [id + nEscritores - 1]);
                break;

            case 5:

                printf ("Cerrando programa ...\n\n");
                return 0;

            default:

                printf ("Opcion no valida. Vuelve a intentarlo\n\n");
        }

    }
}
