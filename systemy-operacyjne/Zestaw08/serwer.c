#include "msg.h"

void obsluga(int signal) {
    printf("\nwyslano sygnal %d, koniec serwera\n", signal);
    exit(EXIT_SUCCESS);
}

void koniec() {
    msgRm(kolejka_serwera);
    msgClose(mqdes_serwer);
}

int main(int argc, char *argv[]) {

mqdes_serwer = msgCreate(kolejka_serwera);

atexit(koniec);
msgInfo(mqdes_serwer);

if(signal(2, obsluga) == SIG_ERR) {                   //przy otrzymaniu sygnalu wykona sie funkcja obsluga()
            perror("blad przy obsludze sygnalu");
            exit(EXIT_FAILURE);
            }

sleep(1);

Komunikat *msg = malloc(sizeof(Komunikat));
int wynik;

while(1) {
msgRecv(mqdes_serwer, msg);         // czekanie na komunikat od klienta
sprintf(kolejka_klienta, "/%d", msg->pid);
mqdes_klient = msgOpen(kolejka_klienta);    // otworzenie kolejki komunikatow klienta

printf("S: pid klienta: %d\n", msg->pid);
printf("S: a: %d\n", msg->a);
printf("S: operacja: %c\n", msg->o);
printf("S: b: %d\n", msg->b);

switch(msg->o){
    case '+':;
    wynik = (msg->a + msg->b);
        break;
    case '-':;
    wynik = (msg->a - msg->b);
        break;
    case '*':;
    wynik = (msg->a * msg->b);
        break;
    case '/':;
    wynik = (msg->a / msg->b);
        break;
}

printf("S: wynik: %d\n", wynik);
msg->pid = wynik;           // podmieniam pid klienta, na wynik
msgSend(mqdes_klient, msg); // przeslanie wyniku
}

free(msg);

}