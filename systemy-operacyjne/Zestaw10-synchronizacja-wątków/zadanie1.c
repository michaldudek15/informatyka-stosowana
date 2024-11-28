#define _XOPEN_SOURCE 500

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#define N 10
#define SEKCJE 3

volatile int licznik = 0; // globalny licznik
volatile bool wybieranie[N];
volatile int kolej[N];

void obsluga(int signal) {
    printf("\033c");
    exit(EXIT_SUCCESS);
}

void* watek(void* ptr) {
    int numer = *(int *)ptr;
    int i, j;
    printf("\033[%d;%dHwatek\033[m\n", numer + 2, 1); // watek
    printf("\033[%d;%dH%d\033[m\n", numer + 2, 8, numer); // numer watku
    for(i = 0; i < SEKCJE; i++){
    wybieranie[numer] = true;
    int max = kolej[0];
    for(j = 0; j < N; j++) {
        if(kolej[j] > max) max = kolej[j];
    }
    kolej[numer] = max + 1;
    wybieranie[numer] = false;
    printf("\033[%d;%dH\033[K\033[1;35mczekam kolej: %d\033[m\n", numer + 2, 16, kolej[numer]);             // czekam
    for(j = 0; j < N; j++) {
        while (wybieranie[j]) ; // watek czeka jesli nie wybral numerka 
        while ( kolej[j] != 0 && (kolej[j] < kolej[numer] || (kolej[j] == kolej[numer] && j < numer)) );
    }
    usleep(500000);
    // sekcja krytyczna

    licznik++;
    printf("\033[%d;%dH\033[K", numer + 2, 16);
    printf("\033[%d;%dH\033[1;31msekcja krytyczna (%d/%d)\033[m\n", numer + 2, 35, i + 1, licznik);     // sekcja krytyczna
    kolej[numer] = 0;
    usleep(500000);

    // koniec sekcji krytycznej

    printf("\033[%d;%dH\033[K\033[1;32mspie\033[m\n", numer + 2, 16);                // spie
    usleep(500000);
    }
    printf("\033[%d;%dH\033[K\033[1;33mzakonczono\033[m\n", numer + 2, 16);

    free(ptr);
    pthread_exit(NULL);
    }

int main(int argc, char* argv[]) {

if(signal(2, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
        }

pthread_t thId[N];
printf("\033c\033[1;1HWATEK\033[1;8HNUMER\033[1;16HSEKCJA PRYWATNA\033[1;35HSEKCJA KRYTYCZNA\033[m\n\n"); // 1;1 1;8 1;16 1;35
int i;
for(i = 0; i < N; i++) {
    int* numer = malloc(sizeof(int));
    *numer = i;
    if(pthread_create(&thId[i], NULL, watek, numer) != 0) {
        perror("blad funkcji pthread_create");
        exit(EXIT_FAILURE);
        }
    }

for(i = 0; i < N; i++) {
    if(pthread_join(thId[i], NULL) != 0) {
        perror("blad funkcji pthread_join");
        exit(EXIT_FAILURE);
        }
    }
    printf("\033[%d;1Hwartosc licznika: \033[1;32m%d\t\t \033[0moczekiwana wartosc licznika: \033[1;32m%d\n", N + 3, licznik, N*SEKCJE);

}