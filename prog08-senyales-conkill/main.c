#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void tratarSenal(int cod_senal);
pid_t pidHijo;
bool final = false;

int main(int argc, char const *argv[])
{
    
    pidHijo = fork();

    switch (pidHijo)
    {
    case -1:
        exit(1);
        break;

    case 0: //es el hijo
        signal(SIGUSR2, tratarSenal);
        signal(SIGINT, SIG_IGN);
        printf("Hijo %d: Esperando señal \n", getpid());
        while (!final) {
            printf("Hijo: Esperando 5 segundos...\n");
            sleep(5);
        }
        break;
    
    default: //es el padre
        signal(SIGINT, tratarSenal);
        printf("Padre %d: Esperando señal \n", getpid());
        pause();
        wait(NULL);
    }
    
    return 0;
}

void tratarSenal(int cod_senal) {

    if (cod_senal == SIGINT) {
        printf("Proceso %d: Recibida la señal %d\n", getpid(), cod_senal);
        printf("Enviando señal al hijo con pid %d en 5 segundos\n", pidHijo);
        sleep(5);
        printf("Envio completado.\n");
        kill(pidHijo, SIGUSR2);
    }
    else if (cod_senal == SIGUSR2) {

        printf("Proceso %d: Recibida la señal %d\n", getpid(), cod_senal);
        final = true;
    }
}