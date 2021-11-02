#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void tratarSenal(int cod_senal);

int main(int argc, char const *argv[])
{
    
    pid_t p_hijo1, p_hijo2;

    
    if((p_hijo1 = fork()) == -1) {

        perror("Error al crear el hijo");
        exit(-1);
    }
    
    if (p_hijo1 == 0) { //es el hijo 1


        signal(SIGUSR1, tratarSenal);
        printf("Hijo 1: pid: %d\n", getpid());
        pause(); //espera a una señal

    }

    else { //aqui el padre

        printf("Padre: He creado un hijo con pid %d\n", p_hijo1);
        if ((p_hijo2 = fork()) == -1) {

            perror("Error al crear el hijo");
            exit(-1);
        }

        if (p_hijo2 == 0) { //es el hijo 2

            printf("Hijo 2: pid: %d\n", getpid());
            sleep(5);
            kill(p_hijo1, SIGUSR1);

        }

        else {
            
            printf("Padre: He creado un hijo con pid %d\n", p_hijo2);
            printf("Padre: Esperando a un hijo...\n");
            printf("El hijo con pid %d finalizó \n", wait(NULL));

            printf("Padre: Esperando a otro hijo...\n");
            printf("El hijo con pid %d finalizó \n", wait(NULL));

        }
    }

    return 0;
}

void tratarSenal(int cod_senal) {

    printf("Proceso %d: He recibido una señal\n", getpid());
}
