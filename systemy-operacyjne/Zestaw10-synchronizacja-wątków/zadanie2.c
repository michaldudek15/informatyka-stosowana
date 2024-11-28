#define _XOPEN_SOURCE 500

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#define N 3
#define SEKCJE 10

volatile int licznik = 0; // globalny licznik
volatile bool wybieranie[N];
volatile int kolej[N];

void* watek(void* ptr) {
    int numer = *(int *)ptr;
    int i, j;
    for(i = 0; i < SEKCJE; i++){
    wybieranie[numer] = true;
    int max = 0;
    for(j = 0; j < N; ++j) {
        if(kolej[j] > max) max = kolej[j];
    }
    kolej[numer] = max + 1;
    wybieranie[numer] = false;

    for(j = 0; j < N; ++j) {
        while (wybieranie[j]) ; // watek czeka jesli nie wybral numerka 
        while ( kolej[j] != 0 && (kolej[j] < kolej[numer] || (kolej[j] == kolej[numer] && j < numer)) );
    }

    // sekcja krytyczna

    __sync_synchronize();
    licznik++;
    kolej[numer] = 0;

    // koniec sekcji krytycznej

    }      
    
    free(ptr);
    return NULL;
    }

//int main(int argc, char* argv[]) {
int main(void) {

pthread_t thId[N];
int i;
for(i = 0; i < N; ++i) {
    int* numer = malloc(sizeof(int));
    *numer = i;
    if(pthread_create(&thId[i], NULL, watek, numer) != 0) {
        perror("blad funkcji pthread_create");
        exit(EXIT_FAILURE);
        }
    }

for(i = 0; i < N; ++i) {
    if(pthread_join(thId[i], NULL) != 0) {
        perror("blad funkcji pthread_join");
        exit(EXIT_FAILURE);
        }
    }
    printf("wartosc licznika: %d\t\toczekiwana wartosc licznika: %d\n", licznik, SEKCJE*N);
}