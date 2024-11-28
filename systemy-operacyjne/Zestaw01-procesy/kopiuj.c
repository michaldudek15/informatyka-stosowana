#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define ROZMIAR_BUFORA 1024

int main(int argc, const char* argv[]) {
	if(argc != 3){ 				// kopiuj.x, plik zrodlowy, plik docelowy
		printf("prawidlowe uzycie programu %s, zla liczba argumentow\n", argv[0]);
		exit(EXIT_SUCCESS);
	}	

	char *bufor = malloc(ROZMIAR_BUFORA);
	if(bufor == NULL) {
		perror("blad tworzenia bufora:");
		exit(EXIT_FAILURE);
		}

	int fd_zrodlo = 0;
	if ((fd_zrodlo = open(argv[1], O_RDONLY)) < 0) {
		perror("blad otwarcia pliku zrodlowego:");
		exit(EXIT_FAILURE);
		}

	int fd_cel = 0;
	if ((fd_cel = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR)) < 0) {
		perror("blad otwarcia pliku docelowego:");
		exit(EXIT_FAILURE);
	}
	

	int licznik = 0;	//tworze licznik, zeby wiedziec kiedy skonczyc wypisywanie do pliku docelowego

	while((licznik = read(fd_zrodlo, bufor, ROZMIAR_BUFORA)) > 0) {	//funkcja read() zwraca 0, gdy dojdzie do konca pliku
		if(write(fd_cel, bufor, licznik) < 0) {
			perror("blad zapisu do pliku docelowego:");
			exit(EXIT_FAILURE);
		}
	}

	if(licznik < 0) {
		perror("blad odczytu z pliku zrodlowego:");
		exit(EXIT_FAILURE);
	}
	// zamykanie deskryptorow i zwalnianie pamieci
	if(close(fd_zrodlo) < 0) {
		perror("blad podczas zamykania pliku zrodlowego:");
	}
	if(close(fd_cel) < 0) {
		perror("blad podczas zamykania pliku docelowego:");
	}	
	free (bufor);			
	
	printf("prawidlowe uzycie programu, zawartosc pliku '%s' zostala skopiowana do pliku '%s'\n", argv[1], argv[2]);
}
