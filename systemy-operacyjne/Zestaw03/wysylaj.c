#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

int id = fork();                        //zapisuje pid procesu potomnego, zeby wiedziec jakiemu procesowi wyslac sygnal
int sygnal = atoi(argv[2]);
switch(id) {
case -1:
    perror("blad funkcji fork()");
	exit(EXIT_FAILURE);
    break;

case 0:
    if(execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL) == -1) {
    perror("blad funkcji execl()");
    exit(EXIT_FAILURE);
    }
    break;

default:
    sleep(1);                           //czekam, zeby proces potomny wykonal wszystko i zaczal czekac na otrzymanie sygnalu
    if (kill(id, 0) == -1) {
        perror("blad funkcji kill()");
        exit(EXIT_FAILURE);
    }
    kill(id, sygnal);                   //wysylam sygnal do procesu potomnego
    wait(NULL);                         //czekam na zakonczenie jedynego procesu potomnego
    break;
    
}

}