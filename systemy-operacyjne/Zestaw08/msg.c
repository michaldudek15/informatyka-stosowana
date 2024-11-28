#include "msg.h"

int msgCreate(const char *name) {
    mqd_t mqdes = mq_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NULL);
    if (mqdes == -1) {
        perror("blad funkcji mq_open()");
        exit(EXIT_FAILURE);
    }
    printf("utworzono kolejke komunikatow: %s, deskryptor: %d\n", name, mqdes);
    return mqdes;
}

int msgOpen(const char *name) {
    mqd_t mqdes = mq_open(name, O_RDWR);
    if (mqdes == -1) {
        perror("blad funkcji mq_open()");
        exit(EXIT_FAILURE);
    }
    printf("otworzono kolejke komunikatow: %s, deskryptor: %d\n", name, mqdes);
    return mqdes;
}

void msgClose(int mqdes) {
    if(mq_close(mqdes) == -1) {
        perror("blad funkcji mq_close()");
        exit(EXIT_FAILURE);
    }
    printf("zamknieto kolejke komunikatow o deskryptorze: %d\n", mqdes);
}

void msgRm(const char *name) {
    if(mq_unlink(name) == -1){
        perror("blad funkcji mq_unlink()");
        exit(EXIT_FAILURE);
    }
    printf("usunieto kolejke komunikatow: %s\n", name);
}

void msgSend(int msgid, Komunikat *msg) {
    if(mq_send(msgid, (const char*)msg, sizeof(Komunikat) + 1, 1) == -1) {
        perror("blad funkcji mq_send()");
        exit(EXIT_FAILURE);
    }
}

void msgRecv(int msgid, Komunikat *msg) {
    if(mq_receive(msgid, (char *)msg, 9000, NULL) == -1) {
        perror("blad funkcji mq_receive");
        exit(EXIT_FAILURE);
    }
}

void msgInfo(int msgid) {
    struct mq_attr attr;
    if(mq_getattr(msgid, &attr) == -1) {
        perror("blad funkcji mq_getattr()");
        exit(EXIT_FAILURE);
    }
    printf("mq_flags        :%lX\n", attr.mq_flags);
    printf("mq_maxmsg       :%ld\n", attr.mq_maxmsg);
    printf("mq_msgsize      :%ld\n", attr.mq_msgsize);
    printf("mq_curmsgs      :%ld\n", attr.mq_curmsgs);
}