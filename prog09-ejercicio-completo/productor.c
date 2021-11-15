//importar los módulos .h que necesitemos.
//si necesitamos funciones.h también, y entre comillas.
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>



//declarar la función que gestione las señales, 
//puede ser 1 para las dos señales SIGUSR1 y SIGUSR2
// o una común que discrimine por el código de señal
// que viene en el parámetro.

//implementar el main.
//en este caso, el main recibirá como parámetro
//el pid del consumidor 
//el parámetro estará en argv[1]

void tratarSenal(int senyal);

int main(int argc, char const *argv[1]) {

    pid_t productor;

    bool final = false;
     // Aquí en lugar de lanzar el hilo, hay que
        // lanzar el proceso productor.exe (pág. 7 apuntes)
        // pasándole por parámetro el pid del consumidor
        //  productor = fork(); //esto sólo el padre.
        if (productor == -1)
        {
            perror("Error creando al productor.");
            exit(2);
        }
        if (productor == 0)
        {                 //código del productor. Sólo escribirá en el pipe así que...
            close(fd[0]); //cierra el extremo de lectura.
            unsigned int monedas_producidas = 0;
            printf("[Productor]: Iniciando producción bajo demanda... Esperando señal de producción\n");
            pause();
            while (!final)
            {
                printf("[Productor]: Produciendo monedas, tardaré 3 segundos en producir entre %d y %d monedas.\n", MIN, MAX);
                //genero monedas
                sleep(3);
                monedas_producidas = int_aleatorio(MIN, MAX);
                printf("[Productor]: Producidas %u monedas.\n", monedas_producidas);
                //escribo las monedas en el pipe
                write(fd[1], &monedas_producidas, sizeof(unsigned int));
                //notifico al consumidor que hay monedas disponibles para leer
                kill(consumidor, SIGUSR1);
                printf("[Productor]: Consumidor notificado. Esperando señal para continuar...\n");
                pause();
            }
            //cerrar pipe (la parte de escritura)
            close(fd[1]);
        }
        else
        { // Código del padre, me quedo esperando la señal inicial:
            pause();
            while (!final)
            {
                //Si he recibido una señal y no se ha acabado la construcción, es que tengo que notificar al prodcutor
                kill(productor, SIGUSR1);
                printf("[Padre]: Esperando una señal...\n");
                pause(); //me quedo esperando la siguiente señal.
            }
            //el consumidor ha terminado, lo espero.
            wait(NULL);
            //enviando la señal de finali al productor para que se desbloquee actualizando su valor de final.
            kill(productor, SIGUSR2);
            //esperando al productor
            wait(NULL);
        }
    }
    
    printf("El parámetro es %s, pero no es de tipo pid_t, así que lo tengo que convertir. atoi (o mejor atol) puede ser una buena opción.",argv[1]);
    return 0;
}

void tratarSenal(int senyal) {

    if (senyal == SIGUSR1) {

        
    }

    else if (senyal == SIGUSR2) {
        final = true; 
    }
}