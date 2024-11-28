#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, const char* argv[0]) {
			
switch (fork()) {
		case -1:
			perror("blad funkcji fork()");
			exit(EXIT_FAILURE);
			break;
		case 0: //proces potomny
            sleep(10);
			break;
		default: //proces macierzysty
        sleep(4);
        exit(0);
		break;
		}
}