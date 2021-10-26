#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//definimos manejador de señal

void manejadorHijos(int num_signal);
void manejadorPadre(int num_signal);

int main(int argc, char const *argv[]) {
    
    pid_t pid;
    pid = fork(); 

    if (pid == -1) {
        
        perror("Error en el fork");
        exit(1);
    }
    
    if(pid == 0) { //Soy el proceso hijo

        signal(SIGUSR1, manejadorHijos);
        printf("[Proceso: %d]: Manejador activado.\n", getpid());
        pause();
    }

    else { //Soy el proceso padre

        signal(SIGUSR1, manejadorPadre);
        printf("[Proceso: %d]: Manejador activado.\n", getpid());
        pause();
        pid_t pid_hijo = wait(NULL);

    }
    return 0;
}

//implementando manejadores
void manejadorHijos (int num_signal) {

    printf("Soy el manejador de señales para hijos\n");

}

void manejadorPadre(int num_signal) {

    printf("Soy el manejador de señales para el padre\n");

}
