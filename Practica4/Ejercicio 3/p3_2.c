#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *ramos(void *arg)
{

    printf("Ramos ");
    return 0;
}

void *pique(void *arg)
{

    printf("Pique ");
    return 0;
}

void *jordi(void *arg)
{

    printf("Jordi-Alba ");
    return 0;
}

void *thiago(void *arg)
{

    printf("Thiago ");
    printf("Silva ");
    return 0;
}

int main(int argc, char const *argv[])
{

    pthread_t hilos[4];
    int error;

    printf ("De Gea ");

    error = pthread_create (&hilos[0], NULL, (void *) jordi, NULL);

    if (error != 0)
    {
        printf ("Ha habido un error en la creacion del hilo 0\n\n");
        return 0;
    }

    error = pthread_create (&hilos[1], NULL, (void *) pique, NULL);

    if (error != 0)
    {
        printf ("Ha habido un error en la creacion del hilo 1\n\n");
        return 0;
    }

    error = pthread_create (&hilos[2], NULL, (void *) ramos, NULL);

    if (error != 0)
    {
        printf ("Ha habido un error en la creacion del hilo 2\n\n");
        return 0;
    }

    printf ("Carvajal ");
    pthread_join(hilos[0], NULL);

    error = pthread_create (&hilos[3], NULL, (void *) thiago, NULL);

    if (error != 0)
    {
        printf ("Ha habido un error en la creacion del hilo 3\n\n");
        return 0;
    }

    pthread_join(hilos[1], NULL);
    pthread_join(hilos[2], NULL);

    printf("Busquets ");
    printf("Isco ");
    printf("Aspas ");

    pthread_join(hilos[3], NULL);

    printf("Morata\n\n");

    return 0;
}