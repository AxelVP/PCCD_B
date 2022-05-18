#include <stdio.h>

int main(int argc, char const *argv[])
{
    while (1)
    {
        printf ("Caminando por mi habitacion");

        while (getchar () != '\n');

        printf ("Intentando entrar en mi seccion critica ...\n");
        printf ("Dentro de mi Seccion Critica");

        while (getchar () != '\n');

        printf ("He salido de mi Seccion Critica\n");
    }

    return 0;
}
