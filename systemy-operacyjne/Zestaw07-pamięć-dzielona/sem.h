#ifndef SEM_H
#define SEM_H

#define _XOPEN_SOURCE 500

#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

typedef sem_t *semid;

int wartosc_semafora; // miejsce, gdzie zapisana jest aktualna wartosc semafora
semid sem_prod;   // 'identyfikator' semafora dla producenta
semid sem_kons;   // 'identyfikator' semafora dla konsumenta

semid semCreate(const char *name, int val);
void semRemove(const char *name);
semid semOpen(const char *name);
void semClose(semid sem);
void semP(semid sem);
void semV(semid sem);
void semInfo(semid sem, int wartosc_semafora);

#endif