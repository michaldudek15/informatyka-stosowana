#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sem.h"


int main(int argc, char* argv[]) {
int sekcje = atoi(argv[2]);

id_sem = semOpen(nazwa_semafora);

int i;
int numer = 0;
FILE *plik;
for(i = 0; i<sekcje; ++i) {

printf("przed sekcja krytyczna PID: %d ", getpid() );
semInfo(id_sem, wartosc_semafora);
usleep(rand() % 1000000);
semP(id_sem); // sekcja krytyczna

if( (plik = fopen("numer.txt", "r")) == NULL) {
    perror("blad otwarcia pliku numer.txt");
    exit(EXIT_FAILURE);
    }

int wczytano = fscanf(plik, "%i", &numer);
if (wczytano < 0) {
    printf("blad!\n");
}
fclose(plik);
numer++;
usleep(rand() % 1000000);
printf("                                                                 w sekcji krytycznej PID: %d, petla numer: %d ", getpid(), (i+1) );
semInfo(id_sem, wartosc_semafora);
printf("aktualny numer %d\n", numer);

if( (plik = fopen("numer.txt", "w")) == NULL) {
    perror("blad otwarcia pliku numer.txt");
    exit(EXIT_FAILURE);
    }
fprintf(plik, "%d", numer);
fclose(plik);

semV(id_sem); // koniec sekcji krytycznej

printf("po sekcji krytycznej PID: %d ", getpid() );
semInfo(id_sem, wartosc_semafora);  
}

semClose(id_sem);
}