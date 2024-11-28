#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "procinfo.h"
#define FORKI 3

int main(int argc, const char* argv[]) {

	int i = 0;
	int pokolenie = 0;
	int dzieci = 0;
	
	printf("pokolenie 0. ");
	procinfo(argv[0]); //identyfikatory procesu poczatkowego
	
	for(i = 0; i < FORKI; i++ ) {
		switch (fork()) {
		case -1:
			perror("blad funkcji fork()");
			exit(EXIT_FAILURE);
			break;
		case 0: //proces potomny
			pokolenie++;
			dzieci = 0; //zaczynam liczyc liczbe procesow potomnych kiedy proces zaczyna istniec
			printf("pokolenie %d. ", pokolenie);
			procinfo(argv[0]);
			sleep(1); //grupuje procesy pokoleniami
			break;
		default: //proces macierzysty
		dzieci++; //za kazdym razem kiedy fork zwroci PID procesu potomnego trzeba czekac na kolejnego potomka
		break;
		}
        if(dzieci==1) { //przerywam petle for kiedy proces stworzy tylko jednego potomka
            break;
        }
	}
for( i = 0; i < dzieci; i++) {  //czekanie na procesy dzieci
	 if(wait(NULL) <= 0) {
		 perror("blad funkcji wait()");
	 }; 
	}

}