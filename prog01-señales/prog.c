#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void gestionar_interrupcion(int senal) {

    printf("Recibida la señal número %d\n", senal);

} 

int main (int argc, char const *argv[]) {

    signal(SIGINT, gestionar_interrupcion);
    printf("hola mundo\n");
    sleep(20);
    printf("hola mundo 2\n");
    return 0;
}