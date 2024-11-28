#define _XOPEN_SOURCE 500
#include "shmem.h"

int main(int argc, char *argv[]) {

/* sprawdzenie liczby argumentów */
if(argc > 3 || argc == 1) {
    printf("nieodpowiednia liczba argumentow: %d, program mozna wywolac z maksymalnie dwoma argumentami\n", argc-1);
    exit(EXIT_SUCCESS);
}

if (strcmp(argv[1],"c") == 0 && argc == 2) {
    printf("przy wywolaniu opcji 'c' nalezy podac tez rozmiar w bajtach segmentu pamieci dzielonej\n");
    exit(EXIT_SUCCESS);
}

int akcja = 0;

if (strcmp(argv[1],"c") == 0) {
    akcja = 1;
    printf("dziala kox\n");
}

if (strcmp(argv[1],"d") == 0) {
    akcja = 2;
}

if (strcmp(argv[1],"r") == 0) {
    akcja = 3;
}

if (strcmp(argv[1],"w") == 0 && argc != 2) {
    printf("przy wywolaniu opcji 'w' nalezy podac tez plik tekstowy do skopiowania do pamieci dzielonej\n");
    exit(EXIT_SUCCESS);
}

if (strcmp(argv[1],"w") == 0) {
    akcja = 4;
}

if (strcmp(argv[1],"i") == 0) {
    akcja = 5;
}

if(akcja == 0) {
    printf("jako argument przy wywolywaniu programu podaj 'c <rozmiar>', 'd', 'r', 'w < input.txt' lub 'i'\n");
    exit(EXIT_SUCCESS);
}

int fd_shm;
int licznik;
char *ptr;

switch(akcja) { 
    case 1:; // tworzy segment pamieci dzielonej
        size = atoi(argv[2]); 
        fd_shm = shmCreate(name, size);
        break;
    case 2:; // usuwa segment pamieci dzielonej
        shmRm(name);
        break;
    case 3:; // wypisuje zawartosc pamieci dzielonej
        fd_shm = shmOpen(name);
        size = shmSize(fd_shm);
        ptr = shmMap(fd_shm, size);        
        printf("zawartosc pamieci dzielonej:\n%s\n", ptr);
        shmClose(ptr, fd_shm, size);
	    break;
    case 4:; // kopiuje zawartosc standardowego wejscia do pamieci dzielonej
        fd_shm = shmOpen(name);
        size = shmSize(fd_shm);
        printf("rozmiar segmentu pamieci dzielonej: %d\n", shmSize(fd_shm));
        ptr = shmMap(fd_shm, size);
        licznik = read(STDIN_FILENO, ptr, size);
        if (licznik < 0) {
            perror("blad funkcji read");
            exit(EXIT_FAILURE);
            }
        printf("rozmiar danych w input.txt: %d\n", licznik);
        shmClose(ptr, fd_shm, size);
        break;
    case 5:; // wypisuje informacje o pamieci dzielonej
        fd_shm = shmOpen(name);
        size = shmSize(fd_shm);
        shmInfo(fd_shm);
        ptr = shmMap(fd_shm, size);
        shmClose(ptr, fd_shm, size);
        break;
    default:; // wypisuje informacje o uzyciu tego programu
        printf("jako argument przy wywolywaniu programu podaj 'c <rozmiar>', 'd', 'r', 'w < <input.txt>' lub 'i'\n");
        exit(EXIT_SUCCESS);
        break;
}
}