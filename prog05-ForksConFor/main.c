//Crear un programa usando 2 bucles
//Crea 5 hijos definidos en una constante
//Cada uno de ellos imprime su pid y el de su padre y luego un sleep
//Despues de crear hijos, el padre se queda esperando en otro bucle
//Espera tanto como numero de hijos tenga

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define numHijos 5


int main(int argc, char const *argv[]) {

    pid_t pid_padre = getpid();
    pid_t pid;
    
    for (int i = 0; i < numHijos && pid_padre == getpid(); i++) {
        
        pid = fork();

        if (pid == 0) {
            //es un hijo
        }

        else {

            printf("[Padre %d]: Proceso hijo %d creado. \n" , getpid());
        }
    }

    if (getpid() == pid_padre) {

        int estado_proceso;
        pid_t pid_hijo;
        
        //proceso padre espera a los hijos

        for (int i = 0; i < numHijos; i++) {

            pid_hijo = wait(&estado_proceso);
            printf("[Padre]: Hijo %d ha terminado.\n", getpid());
        }

        printf("[Padre %d]: Todos mis procesos hijo han terminado.\n");
    }

    else {

        printf("[Hijo %d]: Mi padre es %d\n", getpid(), getppid());
        sleep(1);
    }
    
    

    return 0;
}
