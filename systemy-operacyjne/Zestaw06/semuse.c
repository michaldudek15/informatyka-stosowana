#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sem.h"

int main(int argc, char* argv[]) {

if(argc != 2) {
    printf("prawidlowe uzycie programu %s, nieprawidlowa liczba argumentow\n", argv[0]);
    exit(EXIT_SUCCESS);
}

int akcja = 0;

if (strcmp(argv[1],"i") == 0) {
    akcja = 1;
}

if (strcmp(argv[1],"r") == 0) {
    akcja = 2;
}

if (strcmp(argv[1],"p") == 0) {
    akcja = 3;
}

if (strcmp(argv[1],"v") == 0) {
    akcja = 4;
}

if (strcmp(argv[1],"q") == 0) {
    akcja = 5;
}

if(akcja == 0) {
    printf("jako argument przy wywolywaniu programu podaj 'i', 'r', 'p', 'v' lub 'q'\n");
    exit(EXIT_SUCCESS);
}

switch(akcja) { 
    case 1:; // 'i' inicjuje semafor i wypisuje o nim informacje
        id_sem = semCreate(nazwa_semafora, 1);
        printf("adres semafora: %p\n",  (void *)id_sem);
        semInfo(id_sem, wartosc_semafora);
        semClose(id_sem);
        break;
    case 2:; // 'r' usuwa semafor
        semRemove(nazwa_semafora);
        break;
    case 3:; // 'p' opuszcza semafor i wypisuje o nim informacje
        id_sem = semOpen(nazwa_semafora);
        semP(id_sem);
        semInfo(id_sem, wartosc_semafora);
        semClose(id_sem);
        break;
    case 4:; // 'v' podnosi semafor i wypisuje o nim informacje
        id_sem = semOpen(nazwa_semafora);
        semV(id_sem);
        semInfo(id_sem, wartosc_semafora);
        semClose(id_sem);
        break;
    case 5:; // 'q' wypisuje informacje o semaforze
        id_sem = semOpen(nazwa_semafora);
        printf("adres semafora: %p\n",  (void *)id_sem);
        semInfo(id_sem, wartosc_semafora);
        semClose(id_sem);
        break;
    default:;
        printf("blad programu\n");
        exit(EXIT_FAILURE);
        break;
}



}