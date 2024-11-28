#define _XOPEN_SOURCE 500
#define NBUF 5 // liczba elementow bufora
#define NELE 4 // rozmiar elementu bufora

#include "shmem.h"
#include "sem.h"

typedef struct {
    int head;        // pierwszy element do odczytu
    int tail;        // element za ostatnim zapisanym elementem
    char buf[NBUF][NELE];
} Segment;

void pop(int licznik, int fd_schowek, Segment *wpd) {
    while (licznik > 0) { // pobranie towaru
        semP(sem_kons);
        licznik = write(fd_schowek, wpd->buf[wpd->head], 1);
        printf("konsument: %s,      head = %d\n", wpd->buf[wpd->head], wpd->head);
        usleep(rand() % 100000);
        wpd->head++;
        if(wpd->head == NBUF) wpd->head = 0;
        if(strcmp(wpd->buf[wpd->head], "\0") == 0) break;
        semV(sem_prod);
        } 
}

int main(int argc, char* argv[]) {

printf("poczatek konsumenta\n");

const char* PROD = "/sem_producenta";
const char* KONS = "/sem_konsumenta";

int fd_shm; // deskryptor segmentu pamieci dzielonej
int fd_schowek;

if ((fd_schowek = open("schowek.txt", O_WRONLY)) < 0) {
		perror("blad otwarcia pliku schowek.txt");
		exit(EXIT_FAILURE);
		}

sem_prod = semOpen(PROD);
sem_kons = semOpen(KONS);
fd_shm = shmOpen(name);
size = shmSize(fd_shm);

Segment *wpd = (Segment *) shmMap(fd_shm, size);
wpd->head = 0;

pop(1, fd_schowek, wpd);

semClose(sem_prod); 
semClose(sem_kons);
shmClose(wpd, fd_shm, size);
printf("koniec konsumenta\n");
}