#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    
    //duplico el proceso
    pid_t pid1 = fork();
    //duplico el proceso de nuevo
    pid_t pid2 = fork();

    //se devolveran 4 holas en total
    printf("[Proceso]: %d | Hola.\n", getpid());
    sleep(1);

    return 0;
}
