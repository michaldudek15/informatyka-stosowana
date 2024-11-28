CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:=
LDLIBS		:=



.PHONY: all clean

all: producent.x konsument.x fifo.x

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o *.x 

konsument.x: konsument.o
producent.x: producent.o
fifo.x: fifo.o 
konsument.o: konsument.c
producent.o: producent.c
fifo.o: fifo.c
