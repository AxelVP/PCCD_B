#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaforoGeneral;

typedef struct
{

    sem_t *semaforo[2];
    int numEscritor;
} envio;

void *funEscritor(envio *datos)
{

    while (1)
    {

        printf("[Escritor %i] -> Esperando a intentar escribir ...\n", datos->numEscritor);
        sem_wait(datos->semaforo[0]);

        printf("[Escritor %i] -> Intentando escribir ...\n", datos->numEscritor);
        sem_wait(&semaforoGeneral);

        printf("[escritor %i] -> Escribiendo ...\n", datos->numEscritor);
        sem_wait(datos->semaforo[1]);

        printf("[Escritor %i] -> Fin de la lectura\n", datos->numEscritor);
        sem_post(&semaforoGeneral);
    }
}

int main(int argc, char const *argv[])
{
    int nEscritores = atoi(argv[1]), i, error, opcion, escritor;
    sem_t semaforo[2 * nEscritores];
    pthread_t hilos[nEscritores];
    envio datos[nEscritores];

    error = sem_init(&semaforoGeneral, 0, 1);

    if (error != 0)
    {

        printf("Error al crear el semaforo general. Cerrando programa ...\n\n");
        return 0;
    }

    for (i = 0; i < 2 * nEscritores; i++)
    {

        error = sem_init(&semaforo[i], 0, 0);

        if (error != 0)
        {

            printf("Error al crear el semaforo del escritor %i. Cerrando programa ...\n\n", i);
            return 0;
        }
    }

    for (i = 1; i <= nEscritores; i++)
    {

        datos[i - 1].semaforo[0] = &semaforo[i - 1];
        datos[i - 1].semaforo[1] = &semaforo[i + nEscritores - 1];
        datos[i - 1].numEscritor = i;

        error = pthread_create(&hilos[i], NULL, (void *)funEscritor, &datos[i - 1]);

        if (error != 0)
        {

            printf("Error al crear el hilo del escritor %i. Cerrando programa ...\n\n", i);
            return 0;
        }
    }

    while (1)
    {

        sleep(1);
        printf(" 1 - Intentar escribir\n 2 - Finalizar escribir\n 3 - Salir\n\n   Elige una opcion: ");
        scanf("%i", &opcion);
        fflush(stdin);

        switch (opcion)
        {

        case 1:

            printf("Introduzca el numero del escritor (de 1 a %i): ", nEscritores);
            scanf("%i", &escritor);
            fflush(stdin);

            sem_post(&semaforo[escritor - 1]);
            break;

        case 2:

            printf("Introduzca el numero del escritor (de 1 a %i): ", nEscritores);
            scanf("%i", &escritor);
            fflush(stdin);

            sem_post(&semaforo[escritor + nEscritores - 1]);
            break;

        case 3:

            printf("Saliendo del programa ...\n\n");
            return 0;

        default:

            printf("Seleccion incorrecta. Vuelva a intentarlo\n\n");
        }
    }
}