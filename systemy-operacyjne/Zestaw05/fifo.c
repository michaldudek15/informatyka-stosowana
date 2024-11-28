#define _XOPEN_SOURCE 500
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const char *potok;
void koniec();

int main(int argc, const char *argv[]) {

if (argc != 4) {
    printf("przy wywolywaniu programu podaj nazwe potoku, magazyn.txt oraz schowek.txt\n");
    _exit(EXIT_FAILURE);
}
atexit(koniec);
potok = argv[1];
mkfifo(potok, 0777);

switch(fork()) {
    case -1:
        perror("blad funkcji fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execl("./producent.x", "./producent.x", argv[1], argv[2], argv[3], NULL);
        break;
    default:
        break;
}

switch(fork()) {
    case -1:
        perror("blad funkcji fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execl("./konsument.x", "./konsument.x", argv[1], argv[2], argv[3], NULL);
        break;
    default:   
        break;
}

wait(NULL);
wait(NULL);

}

void koniec() {
    unlink(potok);
    printf("potok zostal usuniety\n");
    
}