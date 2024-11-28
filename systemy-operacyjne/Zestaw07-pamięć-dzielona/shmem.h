#ifndef SHMEM_H
#define SHMEM_H

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const char name[] = "/pamiec_dzielona";     // /dev/shm
int size; // rozmiar segmentu pamieci dzielonej

int shmCreate(const char* name, int size);  // tworzy pamiec dzielona o nazwie name i rozmiarze size, zwraca deskryptor obiektu pamieci dzielonej
int shmOpen(const char* name);              // otwiera obiekt pamieci dzielonej i zwraca jego deskryptor
void shmRm(const char* name);               // usuwa obiekt pamieci dzielonej o nazwie name
void* shmMap(int fd, int size);             // odwzorowuje obiekt pamieci dzielonej o deskryptorze fd i rozmiarze size w przestrzen adresowa procesu, zwraca adres poczatku odwzorowanego obszaru pamieci dzielonej
void shmClose(void *ptr, int fd, int size); // usuwa odwzorowanie obiektu pamieci dzielonej i zamyka powiazany z nim deskryptor
int shmSize(int fd);                        // zwraca rozmiar pamieci dzielonej okreslonej deskryptorem fd uzywajac funkcji fstat
void shmInfo(int fd);                       // wypisuje informacje o pamieci dzielonej

#endif