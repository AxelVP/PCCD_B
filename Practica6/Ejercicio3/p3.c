/* msgsnd() -> enviar mensajes 
   msgrcv() -> recibir mensajes 
    El proceso de llamada tiene que tener permiso de escritura en la cola de los mensajes para enviar y permisos de lectura para recibir.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long mtype;
    char *mtext;
}mensaje;


int main(int argc, char const *argv[])
{
    int control = 0, tamano = 0;

    if(argc != 2){
        printf("Faltan parametros \n");
        exit(0);
    }

    int id = atoi(argv[1]);

    mensaje.mtext = "Hola, soy un mensaje";
    mensaje.mtype = 1;

    tamano = sizeof(mensaje.mtext);
    control = msgsnd(id, &mensaje, tamano, 0);

    if(control == -1){
        printf("Error al enviar el mensaje, saliendo... \n");
        exit(0);
    }
    printf("Mensaje enviado correctamente a la cola con id : %i \n", id);

    return 0;
}


