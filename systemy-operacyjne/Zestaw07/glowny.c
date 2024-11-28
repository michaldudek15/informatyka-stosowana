#define _XOPEN_SOURCE 500
#define NBUF 5 // rozmiar bufora

#include "shmem.h"
#include "sem.h"

int main(int argc, char* argv[]) {

const char* PROD = "/sem_producenta";
const char* KONS = "/sem_konsumenta";

sem_prod = semCreate(PROD, NBUF);
sem_kons = semCreate(KONS, 0);

int size = 1024;
shmCreate(name, size);

switch (fork()) {
    case -1:;
        break;
    case 0:;
        if(execl("./producent.x", "./producent.x", NULL) == -1) {
            perror("blad funkcji execl()");
            exit(EXIT_FAILURE);
            } 
        break;
    default:;
        break;
    }

switch (fork()) {
    case -1:;
        break;
    case 0:;
        if(execl("./konsument.x", "./konsument.x", NULL) == -1) {
            perror("blad funkcji execl()");
            exit(EXIT_FAILURE);
            } 
        break;
    default:;
        break;
    }

int i;
for( i = 0; i < 2; i++) {  //czekanie na procesy dzieci
	if(wait(NULL) <= 0) {
		perror("blad funkcji wait");
        }; 
    }

semRemove(PROD);
semRemove(KONS);
shmRm(name);
}