#define _XOPEN_SOURCE 500
#include <stdio.h>          // printf()
#include <stdlib.h>         // EXIT_SUCCESS / EXIT_SUCCESS
#include <unistd.h>         // pipe()
#include <sys/wait.h>       // wait()
#include <sys/stat.h>       // open()
#include <fcntl.h>          // open()
void producent(char *argv[], int fd[]);
void konsument(char *argv[], int fd[]);

int main(int argc, char *argv[]) {

if(argc != 3) {
    printf("przy wywolaniu programu podaj pliki magazyn.txt oraz schowek.txt\n");
    exit(EXIT_FAILURE);
}

int fd[2];              // tablica dwuelementowa na deskryptory potoku

if(pipe(fd) == -1) {    
    perror("blad funkcji pipe()");
    exit(EXIT_FAILURE);
}

int pid_macierzysty = getpid();

switch(fork() ) {
    case -1:            // blad
        perror("blad funkcji fork()");
        exit(EXIT_FAILURE);
        break;
    case 0:             // proces potomny, konsument
        close(fd[1]);       // konsument zamyka deskryptor do pisania przed wczytaniem, zeby wiedziec kiedy skonczyc czytac z potoku
        konsument(&argv[0], &fd[0]);
        close(fd[0]);
        break;
    default:            // proces macierzysty, producent
        close(fd[0]);      
        producent(&argv[0], &fd[0]);
        close(fd[1]);       // producent zamyka deskryptor od pisania, zeby konsument wiedzial kiedy ma zakonczyc czytac z potoku
        break;    
}
//printf("wait\n");
if (getpid() == pid_macierzysty) {
    sleep(1);
    wait(NULL);
}

}

void producent(char *argv[], int fd[]) {
    char *bufor = malloc(sizeof(char) * 5);
    if(bufor == NULL) {
		perror("blad tworzenia bufora");
		exit(EXIT_FAILURE);
		}
    int fd_magazyn = 0;
        if( (fd_magazyn = open(argv[1], O_RDONLY)) < 0) {
            perror("blad otwarcia pliku magazyn.txt");
            exit(EXIT_FAILURE);
        }
    int licznik = 0;
    while((licznik = read(fd_magazyn, bufor, sizeof(char) * 5)) > 0) {      // czytanie z magazyn.txt do bufora
        usleep(rand() % 1000000);
        if( write (fd[1], bufor, licznik ) == -1) {
        perror("blad zapisu do potoku");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, "producent: ", sizeof("producent: ") ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, bufor, licznik ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, "\n", sizeof("\n") ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
    }
     if(close(fd_magazyn) == -1) {
		perror("blad podczas zamykania magazynu");
	    }
        free (bufor);
}

void konsument(char *argv[], int fd[]) {
    char *bufor = malloc(sizeof(char) * 5);
    if(bufor == NULL) {
		perror("blad tworzenia bufora");
		exit(EXIT_FAILURE);
		}
    int fd_schowek = 0;
        if( (fd_schowek = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
            perror("blad otwarcia pliku schowek.txt");
            exit(EXIT_FAILURE);
        }
    int licznik = 0;
    while((licznik = read(fd[0], bufor, sizeof(char) * 5)) > 0) {      // czytanie z potoku do bufora
        usleep(rand() % 1000000);
        if( write (fd_schowek, bufor, licznik ) == -1) {
        perror("blad zapisu do schowek.txt");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, "konsument: ", sizeof("konsument: ") ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, bufor, licznik ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
        if( write (STDOUT_FILENO, "\n", sizeof("\n") ) == -1) {
        perror("blad funkcji write()");
        exit(EXIT_FAILURE);
        }
    }
    if(close(fd_schowek) == -1) {
		perror("blad podczas zamykania magazynu");
	    }
        free (bufor);
}