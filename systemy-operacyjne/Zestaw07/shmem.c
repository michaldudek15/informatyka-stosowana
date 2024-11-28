#define _XOPEN_SOURCE 500
#include "shmem.h"

int shmCreate(const char* name, int size) {
    int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("blad funkcji shm_open()");
        exit(EXIT_FAILURE);
    }
    if(ftruncate(fd, size) == -1) {
        perror("blad funkcji ftruncate()");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int shmOpen(const char* name) {
    int fd = shm_open(name, O_RDWR, 0000);
     if (fd == -1) {
        perror("blad funkcji shm_open()");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void shmRm(const char* name) {
    if(shm_unlink(name) == -1) {
        perror("blad funkcji shm_unlink()");
        exit(EXIT_FAILURE);
    }
    printf("usunieto obiekt pamieci dzielonej %s\n", name);
}

void* shmMap(int fd, int size) {
    char *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((void *)ptr == MAP_FAILED) {
        perror("blad funkcji mmap()");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void shmClose(void *ptr, int fd, int size) {
    if(munmap(ptr, size) == -1) {
        perror("blad funkcji munmap()");
        exit(EXIT_FAILURE);
    }
    if(close(fd) == -1) {
        perror("blad funkcji close()");
        exit(EXIT_FAILURE);
    }
}

int shmSize(int fd) {
    struct stat info;
    if(fstat(fd, &info) == -1) {
        perror("blad funkcji fstat()");
        exit(EXIT_FAILURE);
    }
    return info.st_size;
}  

void shmInfo(int fd) {
    struct stat info;
    if(fstat(fd, &info) == -1) {
        perror("blad funkcji fstat()");
        exit(EXIT_FAILURE);
    }
    printf("prawa dostepu: %o\n", info.st_mode);
    printf("rozmiar: %ld\n", info.st_size);
    printf("wlasciciel: %d\n", info.st_uid);
}