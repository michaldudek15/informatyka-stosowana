#define _XOPEN_SOURCE 500
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/wait.h>    

int main(int argc, const char *argv[]) {
sleep(1);
if (argc != 4) {
    printf("przy wywolywaniu programu podaj nazwe potoku, magazyn.txt oraz schowek.txt\n");
    _exit(EXIT_FAILURE);
}

int fd_magazyn = 0;
int fd_potok = 0;
int licznik = 0;
if( (fd_magazyn = open(argv[2], O_RDONLY)) < 0) {
    perror("blad otwarcia pliku magazyn.txt");
    _exit(EXIT_FAILURE);
    }
if( (fd_potok = open(argv[1], O_WRONLY)) < 0) {
    perror("blad otwarcia potoku");
    _exit(EXIT_FAILURE);
    }

char *bufor = malloc(sizeof(char) * 5);
    if(bufor == NULL) {
		perror("blad tworzenia bufora");
		_exit(EXIT_FAILURE);
		}

while( (licznik = read(fd_magazyn, bufor, sizeof(char) * 5)) > 0) {  
    usleep(rand() % 1000000);
    if( write (fd_potok, bufor, licznik ) == -1) {
        perror("blad zapisu do potoku");
        _exit(EXIT_FAILURE);
        }
    if( write (STDOUT_FILENO, "producent: ", sizeof("producent: ") ) == -1) {
        perror("blad funkcji write()");
        _exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, bufor, licznik ) == -1) {
        perror("blad funkcji write()");
        _exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, "\n", sizeof("\n") ) == -1) {
        perror("blad funkcji write()");
        _exit(EXIT_FAILURE);
        }
    }
    if(close(fd_magazyn) == -1) {
		perror("blad podczas zamykania magazynu");
	    }
    if(close(fd_potok) == -1) {
		perror("blad podczas zamykania potoku");
	    }
    free (bufor);
}