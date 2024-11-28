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

void push(int licznik, int fd_magazyn, Segment *wpd) {
    while (licznik > 0) { // produkcja towaru
        semP(sem_prod);
        licznik = read(fd_magazyn, wpd->buf[wpd->tail], 1);
        if(licznik == 0) break;
        printf("                                        producent: %s,  tail = %d\n", wpd->buf[wpd->tail], wpd->tail);
        usleep(rand() % 100000);
        wpd->tail = (wpd->tail + 1) % NBUF;
        semV(sem_kons);
        }
}

int main(int argc, char* argv[]) {

printf("poczatek producenta\n");
const char* PROD = "/sem_producenta";
const char* KONS = "/sem_konsumenta";

int fd_shm; // deskryptor segmentu pamieci dzielonej
int fd_magazyn;

if ((fd_magazyn = open("magazyn.txt", O_RDONLY)) < 0) {
		perror("blad otwarcia pliku zrodlowego:");
		exit(EXIT_FAILURE);
		}

sem_prod = semOpen(PROD);
sem_kons = semOpen(KONS);
fd_shm = shmOpen(name);
size = shmSize(fd_shm);

Segment *wpd = (Segment *) shmMap(fd_shm, size);
wpd->tail = 0;

push(1, fd_magazyn, wpd);

strcpy(wpd->buf[wpd->tail], "\0"); // konsument szuka tego elemntu, zeby wiedziec kiedy zakonczyc dzialanie

semClose(sem_prod);
semClose(sem_kons);
shmClose(wpd, fd_shm, size);
printf("koniec producenta\n");
}

