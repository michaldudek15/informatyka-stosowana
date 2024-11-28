CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
DLIBCFLAGS	:= -O -fPIC
LDLIBS1		:= -L. -lmsg -lrt
LDLIBS2 	:= -L. -lmsg -lmsg -lrt
AR			:= ar rv

.PHONY: all clean

all: libmsg.a libmsg.so serwer.x klient.x

msga.o: msg.c
	$(CC) -c $< -o $@

libmsg.a: msga.o
	$(AR) $@ $<

msgso.o: msg.c
	$(CC) -c $(DLIBCFLAGS) $< -o $@

libmsg.so: msgso.o
	$(CC) -shared -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) -pthread -o $@ $< $(LDLIBS2)

clean:
	rm -f *.o *.x *.a *.so

serwer.x: serwer.o libmsg.so
klient.x: klient.o libmsg.so