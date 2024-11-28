#include "msg.h"

void obsluga(int signal) {
    printf("\nwyslano sygnal %d, koniec serwera\n", signal);
    exit(EXIT_SUCCESS);
}

void koniec() {
    msgClose(mqdes_serwer);         // zamkniece deskryptora serwera
    msgClose(mqdes_klient);         // zamkniecie wlasnego deskryptora
    msgRm(kolejka_klienta);         // usuniecie wlasnej kolejki komunikatow
}

int main(int argc, char *argv[]) {

printf("poczatek procesu o pid: %d\n", getpid());

sprintf(kolejka_klienta, "/%d", getpid());      // utworzenie nazwy kolejki klienta

mqdes_serwer = msgOpen(kolejka_serwera);
mqdes_klient = msgCreate(kolejka_klienta);
msgInfo(mqdes_klient);

atexit(koniec);

if(signal(2, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
            }

char operacja[50];

printf("podaj operacje, tokeny oddzielaj spacjami:\n");
    if(fgets(operacja, 50, stdin) == NULL) {
        perror("blad funkcji fgets()");
        exit(EXIT_FAILURE);
    }


Komunikat *msg = malloc(sizeof(Komunikat));
sscanf(operacja, "%d %c %d", &msg->a, &msg->o, &msg->b); // utworzenie komunikatu

msg->pid = getpid();

msgSend(mqdes_serwer, msg);     // wyslanie komunikatu do serwera

msgRecv(mqdes_klient, msg);     // czekanie na wynik
printf("\nK: wynik: %d\n", msg->pid);

sleep(1);
free(msg);
}