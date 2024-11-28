#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "procinfo.h"
#define FORKI 3

int main(int agc, const char* argv[]) {

	int i = 0;
	int pokolenie = 0;
	int dzieci = 0;

	printf("pokolenie 0. ");
	procinfo(argv[0]); //identyfikatory procesu poczatkowego
	
	for(i = 0; i < FORKI; i++ ) {
		switch (fork()) {
		case -1:
			perror("blad funkcji fork():");
			exit(EXIT_FAILURE);
			break;
		case 0: //proces potomny
            if(setpgid(0,0) < 0) {
				perror("blad funkcji setpgid:");
			}
			pokolenie++;
			dzieci = 0; 
			printf("pokolenie %d. ", pokolenie);
			procinfo(argv[0]);
			sleep(1); //grupuje procesy pokoleniami
			break;
		default: //proces macierzysty
			dzieci++;
			break;
		}
	}

for( i = 0; i < dzieci; i++) {  //czekanie na procesy dzieci
	 if(wait(NULL) <= 0) {
		 perror("blad funkcji wait: ");
	 }; 
	}

}