CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99

.PHONY: all clean

all: zadanie1.x zadanie2.x

%.o: %.c
	$(CC) -pthread $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) -pthread -o $@ $< $(LDLIBS2)

clean:
	rm -f *.o *.x

zadanie1.x: zadanie1.o
zadanie2.x: zadanie2.o