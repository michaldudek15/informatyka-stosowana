CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:= -pthread -L.
LDLIBS		:= -lrt -lsem
AR			:= ar rv

.PHONY: all clean

all: semuse.x libsem.a powielacz.x prog.x

%.a: 
	$(AR) $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)


clean:
	rm -f *.o *.x *.a numer.txt

semuse.x: semuse.o libsem.a 
prog.x: prog.o libsem.a
powielacz.x: powielacz.o libsem.a
libsem.a: sem.o
semuse.o: semuse.c
powielacz.o: powielacz.c
sem.o: sem.c
prog.o: prog.c