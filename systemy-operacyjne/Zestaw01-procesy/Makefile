
CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:=
LDLIBS		:=



.PHONY: all clean

all: main.x kopiuj.x procesy.x lider.x

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o *.x pisz

main.x: main.o procinfo.o
kopiuj.x: kopiuj.o
procesy.x: procesy.o procinfo.o
lider.x: lider.o procinfo.o
procinfo.o: procinfo.c procinfo.h
main.o: main.c procinfo.h
kopiuj.o: kopiuj.c
procesy.o: procesy.c procinfo.h
lider.o: lider.c procinfo.h
