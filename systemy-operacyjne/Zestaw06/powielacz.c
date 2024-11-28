#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sem.h"
void koniec();
void obsluga();

int main(int argc, char* argv[]) {

if(argc != 4) {
    printf("nieprawidlowa liczba argumentow programu %s\nprzykladowe wywolanie programu: \n./powielacz.x ./prog.x 4 10\ntutaj 4 to liczba procesow a 10 to liczba sekcji krytycznych kazdego procesu\n", argv[0]);
    exit(EXIT_SUCCESS);
}

int forki = atoi(argv[2]);
int sekcje = atoi(argv[3]);

int fd_plik;
if( (fd_plik = open("numer.txt", O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
    perror("blad otwarcia pliku numer.txt");
    _exit(EXIT_FAILURE);
    }

int wpisane = write(fd_plik, "0", 1);
if (wpisane < 0) {
    printf("blad!\n");
}

id_sem = semCreate(nazwa_semafora, 1);
        printf("adres semafora: %p, ",  (void *)id_sem);
        semInfo(id_sem, wartosc_semafora);
atexit(koniec);

if(signal(2, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
        }
int i;
for(i = 0; i < forki; ++i) {
    switch (fork()) {
        case -1:
            perror("blad funkcji fork():");
			exit(EXIT_FAILURE);
            break;
        case 0:
            if(execl("./prog.x", "./prog.x", argv[2], argv[3], NULL) == -1) {
                perror("blad funkcji execl()");
                exit(EXIT_FAILURE);
                }   
            break;
        default:
            break;
    }

}
for( i = 0; i < forki; i++) {  //czekanie na procesy dzieci
	 if(wait(NULL) <= 0) {
		 perror("blad funkcji wait: ");
	 }; 
	}
    sleep(1);


FILE *plik;
int numer;
if( (plik = fopen("numer.txt", "r")) == NULL) {
    perror("blad otwarcia pliku numer.txt");
    exit(EXIT_FAILURE);
    }
int wczytano = fscanf(plik, "%i", &numer);
if (wczytano < 0) {
    printf("blad!\n");
}

printf("liczba w pliku: %d, powinno byc: %d\n", numer, (forki*sekcje) );

fclose(plik);

}





void obsluga() {
    printf("\n");
    semRemove(nazwa_semafora);
    _exit(EXIT_SUCCESS);
}

void koniec() {
    semRemove(nazwa_semafora);
}