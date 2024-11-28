#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char* argv[0]) {

printf("pierwszy komunikat\n"); // bez /n ten komunikat nie wypisze sie, poniewaz nie zostanie oprozniony bufor stdout
//fflush(stdout);

if(execl("./potomny.x", "./potomny.x", NULL) == -1) {
    perror("blad funkcji execl()");
    exit(EXIT_FAILURE);
}

printf("drugi komunikat\n"); // drugi komunikat nie wypisze sie, ponieważ funkcja exec zamienia proces ktory ja wywolal innym programem
}