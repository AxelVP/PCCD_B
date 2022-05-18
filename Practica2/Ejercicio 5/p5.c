#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int senalRecibida = 0;

void signal_handler(int senal)
{
    senalRecibida = senal;
}


int main(int argc, char const *argv[])
{
    int i = 0, numMuertos = 0, carv = 0, pidMuerto = -1;
    int muertosBusquets = 0, muertosMorata = 0;
    int pid [4] = {-1, -1, -1, -1};
    char *nivel0 [3] = {"Ramos ", "Piqué ", "Jordi-Alba "};
    struct sigaction sig;

    sig.sa_handler = signal_handler;
    sigaction(SIGCHLD, &sig, NULL);
    printf("De Gea ");

    for (i = 0; i < 3; i++)
    {
        pid [i] = fork();

        if (pid [i] == 0)
        {
            printf("%s", nivel0[i]);
            return 0;
        }
        else if (carv == 0)
        {
            printf("Carvajal ");
            muertosBusquets++;
            carv = 1;
        }
    }

    do
    {
        pidMuerto = wait (NULL);
        numMuertos++;

        if (pidMuerto == pid [0] || pidMuerto == pid [1])
        {
            muertosBusquets ++;
        } 
        else if (pidMuerto == pid [2])
        {
            muertosBusquets++;
            pid [3] = fork();

            if (pid [3] == 0)
            {
                printf("Thiago ");
                printf("Silva ");
                return 0;
            }
        }
        else if (pidMuerto == pid [3])
        {
            muertosMorata ++;
        }

        if (muertosBusquets == 4)
        {
            printf("Busquets ");
            printf("Isco ");
            printf("Aspas ");
            muertosBusquets++;
        }

        if (muertosMorata == 1)
        {
            printf("Morata ");
            muertosMorata++;
        }

    } while (muertosMorata < 2); // Esto al final se cambia a 10

    printf("\n");

    return 0;
}