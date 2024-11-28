CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:=
LDLIBS		:=



.PHONY: all clean

all: obsluga.x wysylaj.x grupa.x

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o *.x 

obsluga.x: obsluga.o 
wysylaj.x: wysylaj.o obsluga.x
grupa.x: grupa.o obsluga.x
obsluga.o: obsluga.c 
wysylaj.o: wysylaj.c 
grupa.o: grupa.c
