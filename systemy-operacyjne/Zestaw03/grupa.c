#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void potomny_fork(int argc, char* argv[]);

int main(int argc, char* argv[]) {

int sygnal = atoi(argv[2]);
int pgid = fork();

switch(pgid) {
case -1:
    perror("blad funkcji fork()");
	exit(EXIT_FAILURE);
    break;
case 0:
    if(signal(sygnal, SIG_IGN) == SIG_ERR) {                   //sygnal zostanie zignorowany w procesie macierzystym
            perror("blad przy ignorowaniu sygnalu");
            exit(EXIT_FAILURE);
        }
    setpgid(0,0);                                               //ustawiam pid procesu potomnego jako pgid tego procesu i jego dzieci
    potomny_fork(argc, argv);                                   //tworze trzy procesy potomne
    break;
default:
    sleep(1);                                                    //czekam, zeby proces potomny wykonal wszystko i zaczal czekac na otrzymanie sygnalu
     if (kill(-pgid, 0) == -1) {
        perror("blad funkcji kill()");
        exit(EXIT_FAILURE);
    }
    kill(-pgid, sygnal);
    if(wait(NULL) <= 0) {
		 perror("blad funkcji wait()");
         exit(EXIT_FAILURE);
	 }; 
    break;
}
}

void potomny_fork(int argc, char* argv[]) {
    int dzieci = 0;
    int i = 0;
    for(i = 0; i < 3; i++ ) {
		switch (fork()) {
		case -1:
			perror("blad funkcji fork()");
			exit(EXIT_FAILURE);
			break;
		case 0: //proces potomny
			dzieci = 0; //zaczynam liczyc liczbe procesow potomnych kiedy proces zaczyna istniec
			execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL);
			break;
		default: //proces macierzysty
		dzieci++; //za kazdym razem kiedy fork zwroci PID procesu potomnego trzeba czekac na kolejnego potomka
		break;
		}
        if(dzieci==0) { //przerywam petle for w kazdym z procesow dzieci
            break;
        }
	}
    int* status = malloc(sizeof(int));          //rezerwuje miejsce, gdzie wait zwroci pid procesu na ktory czekal
    for (i=0; i<dzieci; ++i) {
        printf("zakonczenie procesu %d\n", wait(status));
    }
}
 