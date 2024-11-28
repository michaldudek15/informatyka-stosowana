#define _XOPEN_SOURCE 500
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

typedef sem_t *semid;

semid semCreate(const char *name, int val) { // tworzy semafor z wartoscia poczatkowa val
    sem_t *sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
    if(sem == NULL) {
        perror("blad funkcji sem_open()");
        exit(EXIT_FAILURE);
    }
    return sem;
} 

void semRemove(const char *name) { // usuwa semafor
    if(sem_unlink(name) == -1) {
        perror("blad funkcji sem_unlink()");
        exit(EXIT_FAILURE);
    }
    printf("usunieto semafor: %s\n", name);
}

semid semOpen(const char *name) { // uzyskuje dostep do istniejacego semafora
    sem_t *sem = sem_open(name, 0);
    if(sem == NULL) {
        perror("blad funkcji sem_open()");
        exit(EXIT_FAILURE);
    }
    return sem;
}

void semClose(semid sem) { // zamyka semafor w danym procesie
    if(sem_close(sem) == -1) {
        perror("blad funkcji sem_close()");
        exit(EXIT_FAILURE);
    }
}

void semP(semid sem) { // opuszcza semafor; zmniejsza wartosc semafora o 1 lub czeka
    if(sem_wait(sem) == -1) {
        perror("blad funkcji sem_wait()");
        exit(EXIT_FAILURE);
    }
}

void semV(semid sem) { // podnosi semafor; zwieksza wartosc semafora o 1 lub wznawia czekajacy proces
    if(sem_post(sem) == -1) {
        perror("blad funkcji sem_post()");
        exit(EXIT_FAILURE);
    }
}

void semInfo(semid sem, int wartosc_semafora) { // wypisuje informacje o wartosci semafora lub liczbie czekajacych procesow
    if(sem_getvalue(sem, &wartosc_semafora) == -1) {
        perror("blad funkcji sem_getvalue()");
        exit(EXIT_FAILURE);
    }
    printf("wartosc semafora: %d\n", wartosc_semafora);
}