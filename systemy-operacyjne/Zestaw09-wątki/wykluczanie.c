#define _XOPEN_SOURCE 500

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define WATKI 6
#define SEKCJE 5

unsigned int licznik;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

void obsluga(int signal) {
    printf("\033c");
    exit(EXIT_SUCCESS);
}

void* watek(void* ptr) {
    int numer = *(int *)ptr;
    pthread_t id = pthread_self();
    printf("\033[%d;1H\033[1;32m--\033[0m utworzono watek o numerze %d i ID %ld\033[m\n", WATKI + numer + 5, numer, id);
    printf("\033[%d;%dHwatek\033[m\n", numer + 2, 1);
    printf("\033[%d;%dH%d\033[m\n", numer + 2, 8, numer);

    int i;
    for(i = 0; i < SEKCJE; i++) {
        printf("\033[%d;%dH\033[K\033[1;35mczekam\033[m\n", numer + 2, 16);             // czekam
        int tmp;
        pthread_mutex_lock(&myMutex);////////////////////////////////////////////////////////////////////////// POCZATEK SEKCJI KRYTYCZNEJ

        tmp = licznik;
        tmp++;
        usleep(200000);
        licznik = tmp;
        printf("\033[%d;%dH\033[K", numer + 2, 16);
        printf("\033[%d;%dH\033[1;31msekcja krytyczna (%d/%d)\033[m\n", numer + 2, 35, i, licznik);     // wypisanie sekcja krytyczna
        usleep(300000);

        pthread_mutex_unlock(&myMutex);///////////////////////////////////////////////////////////////////////// KONIEC SEKCJI KRYTYCZNEJ
        printf("\033[%d;%dH\033[K\033[1;32mspie\033[m\n", numer + 2, 16);                // spie
        usleep(500000);
    }
        printf("\033[%d;%dH\033[K\033[1;33mzakonczono\033[m\n", numer + 2, 16);
    printf("\033[%d;1H\033[K\033[1;36m@@\033[0m zakonczono watek o numerze %d i ID %ld\033[m\n", WATKI + numer + 5, numer, id);
    free(ptr);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

if(signal(2, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
        }

pthread_t thId[WATKI];
printf("\033c\033[1;1HWATEK\033[1;8HNUMER\033[1;16HSEKCJA PRYWATNA\033[1;35HSEKCJA KRYTYCZNA\033[m\n\n"); // 1;1 1;8 1;16 1;35
int i;
for(i = 0; i < WATKI; i++) {
    int* numer = malloc(sizeof(int));
    *numer = i+1;
    if(pthread_create(&thId[i], NULL, watek, numer) != 0) {
        perror("blad funkcji pthread_create");
        exit(EXIT_FAILURE);
    }
    
}
printf("\033[%d;1Hutworzono mutex pod adresem %p", WATKI + 5, ((void *)&myMutex));

for(i = 0; i < WATKI; i++) {
    if(pthread_join(thId[i], NULL) != 0) {
        perror("blad funkcji pthread_join");
        exit(EXIT_FAILURE);
    }
}

if(pthread_mutex_destroy(&myMutex) != 0) {                                      // usuwam mutex
    perror("blad funkcji pthread_mutex_destroy");
    exit(EXIT_FAILURE);
}
printf("\033[0m\033[%d;1H\033[Kusunieto mutex\033[m\n", WATKI + 5);
printf("\033[%d;1Hwartosc licznika: \033[1;32m%d\t\t \033[0moczekiwana wartosc licznika: \033[1;32m%d\n", WATKI + WATKI + 6, licznik, WATKI*SEKCJE);
printf("\033[%d;%dH\033[m\n", WATKI + WATKI + 7, 1);
}