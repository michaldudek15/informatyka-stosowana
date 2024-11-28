CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99

.PHONY: all clean

all: wykluczanie.x

%.o: %.c
	$(CC) -pthread $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) -pthread -o $@ $< $(LDLIBS2)

clean:
	rm -f *.o *.x

wykluczanie.x: wykluczanie.o