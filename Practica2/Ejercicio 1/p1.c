#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int nMuertos = 0, nProc = 3, senalRecibida = -1;

void signal_handler (int senal) {

    senalRecibida = senal;
}


int main (int argc, char const *argv[]) {
    
    struct sigaction sig;
    int i = 0;
    sig.sa_handler = signal_handler;
    sig.sa_flags = SA_RESTART;
    
    sigaction (SIGCHLD, &sig, NULL);

    for (i = 0; i < nProc; i++) {

        int procHijo = fork ();

        if (procHijo == 0) {

            printf ("Soy el proceso %i y mi padre es el %i\n", getpid (), getppid ());
            sleep ((i + 2) * 2);
            kill (getpid (), SIGCHLD);
            return 0;
        }
    }

    while (nMuertos < nProc) {

        pause ();
    
        switch (senalRecibida) {

            case SIGCHLD:

                nMuertos ++;
                printf ("Un aliado ha sido derrotado\n");
                break;

            default:
                printf ("Cagamos\n");
        }
    }

    printf ("El equipo de niños ha sido :derrotado\n\n");

    return 0;
}
