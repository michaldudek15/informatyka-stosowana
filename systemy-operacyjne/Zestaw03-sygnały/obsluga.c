#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void obsluga(int sygnal) {
    printf("dostalem sygnal numer %d\n", sygnal);
}

int main (int argc, char* argv[]) {

if(argc != 3) { 				                        // nazwa programu, rodzaj akcji, numer sygnału
		printf("prawidlowe uzycie programu %s, nieprawidlowa liczba argumentow\n", argv[0]);
		exit(EXIT_SUCCESS);
	}	

printf("nazwa procesu: %s | identyfikatory: UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d  \n",
		argv[0], getuid(), getgid(), getpid(), getppid(), getpgrp());


int akcja = 0;

int sygnal = atoi(argv[2]);                             //funkcja signal() przyjmuje jako pierwszy argument numer sygnalu o typie int

if(sygnal == 9 || sygnal == 19) {                       //sygnalow SIGSTOP i SIGKILL nie mozna przechwycic ani ignorowac
    printf("ten sygnal nie moze zostac obsluzony\n");
    exit(EXIT_SUCCESS);
}
if (strcmp(argv[1],"d") == 0) {
    akcja = 1;
}

if (strcmp(argv[1],"i") == 0) {
    akcja = 2;
}

if (strcmp(argv[1],"p") == 0) {
    akcja = 3;
}

if(akcja == 0) {
    printf("jako pierwszy argument funkcji main podaj 'd', 'i' lub 'p'\n");
    exit(EXIT_SUCCESS);
}

switch(akcja) {
    case 1:
        if(signal(sygnal, SIG_DFL) == SIG_ERR) {                   //sygnal wykona sie domyslnie
            perror("blad przy domyslnej obsludze sygnalu");
            exit(EXIT_FAILURE);
        }
        break;

    case 2:
        if(signal(sygnal, SIG_IGN) == SIG_ERR) {                   //sygnal zostanie zignorowany
            perror("blad przy ignorowaniu sygnalu");
            exit(EXIT_FAILURE);
        }
        break;

    case 3:
        if(signal(sygnal, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
        }
        break;
}

pause();                                             //czekam na otrzymanie sygnalu             

}