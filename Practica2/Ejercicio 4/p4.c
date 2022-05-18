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
    int i = 0, procTerm = -1, status = -1;
    sig.sa_handler = signal_handler;
    sig.sa_flags = SA_RESTART;

    sigaction(SIGCHLD, &sig, NULL);

    for (i = 0; i < nProc; i++)
    {

        int procHijo = fork ();

        if (procHijo == 0)
        {
            char * lineaEnvio = "JAAACH";
            //sprintf (lineaEnvio, "Soy el proceso %i \n", i);

            printf("Soy el proceso %i y mi padre es el %i\n", getpid(), getppid());
            execl ("p4hijo", lineaEnvio, (char *) NULL);
            sleep ((i + 2) * 2);
            kill (getpid (), SIGCHLD);
            exit (1);
        }
    }

    while (nMuertos < nProc)
    {

        procTerm = wait(&status);

        switch (senalRecibida)
        {

        case SIGCHLD:

            nMuertos++;
            printf("\nMi niño %i ha muerto (codigo de finalizacion: %i)", procTerm, status);
            break;

        default:
            break;
        }
    }

    printf("\nEl equipo de niños ha sido :derrotado\n\n");

    return 0;
}
