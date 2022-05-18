#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int nMuertos = 0, nProc = 3, senalRecibida = -1;

void signal_handler(int senal)
{

    senalRecibida = senal;
}

int main(int argc, char const *argv[])
{

    struct sigaction sig;
    int i = 0, status = 0, procTerm;
    int procHijo [nProc]; 
    sig.sa_handler = signal_handler;
    sig.sa_flags = SA_RESTART;

    sigaction(SIGCHLD, &sig, NULL);

    for (i = 0; i < nProc; i++)
    {

        procHijo [i] = fork();

        if (procHijo [i] == 0)
        {

            printf("Soy el proceso %i y mi padre es el %i\n", getpid(), getppid());
            sleep((i + 2) * 2);
            kill(getpid(), SIGCHLD);
            exit (2);
        }
    }

    for (i = 0; nMuertos < nProc; i++)
    {

        procTerm = waitpid (procHijo [i], &status, 0);

        switch (senalRecibida)
        {

        case SIGCHLD:

            nMuertos++;
            printf ("Mi niño %i ha muerto (codigo de finalizacion: %i)\n", procTerm, status);
            break;

        default:
            printf("Cagamos\n");
        }
    }

    printf("El equipo de niños ha sido :derrotado\n\n");

    return 0;
}
