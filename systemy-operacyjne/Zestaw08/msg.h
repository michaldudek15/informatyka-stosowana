#ifndef MSG_H
#define MSG_H

#define _XOPEN_SOURCE 500

#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

const char *kolejka_serwera = "/serwer";
char kolejka_klienta[10];
int mqdes_serwer;
int mqdes_klient;

typedef struct {
    int pid; // identyfikator klienta
    int a; // pierwsza skladowa dzialania
    char o; // operacja
    int b; // druga skladowa dzialania
} Komunikat;

int msgCreate(const char *name); // tworzy kolejke komunikatow o nazwie name i zwraca do niej deskryptor
int msgOpen(const char *name); // otwiera kolejke komunikatow o nazwie name i zwraca do niej deskryptor
void msgClose(int msgid); // zamyka dostep do kolejki o deskryptorze msgid
void msgRm(const char *name); // usuwa kolejke komunikatow o nazwie name
void msgSend(int msgid, Komunikat *msg); // wysyla komunikat wskazywany przez msg do kolejki o identyfikatorze msgid
void msgRecv(int msgid, Komunikat *msg); // odbiera z kolejki msgid komunikat i zapisuje go do msg
void msgInfo(int msgid); // wypisuje wszystkie informacje o kolejce komunikatow uzyskane przy pomocy mq_getattr()

#endif