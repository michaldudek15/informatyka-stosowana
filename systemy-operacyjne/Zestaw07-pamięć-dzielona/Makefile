CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
DLIBCFLAGS	:= -O -fPIC
LDLIBS1		:= -L. -lshmem -lrt
LDLIBS2		:= -L. -lshmem -lrt -Wl,-R ./
LDLIBS3		:= -L. -lshmem -lsem -lrt
AR			:= ar rv

.PHONY: all clean

all: libsem.a libshmem.so shmemuse1.x shmemuse2.x konsument.x producent.x glowny.x

sem.o: sem.c
	$(CC) -c $<

libsem.a: sem.o
	$(AR) $@ $<

shmem.o: shmem.c
	$(CC) -c $(DLIBCFLAGS) $<

libshmem.so: shmem.o
	$(CC) -shared -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

shmemuse1.x: shmemuse.o
	$(CC) -o $@ $< $(LDLIBS1)

shmemuse2.x: shmemuse.o
	$(CC) -o $@ $< $(LDLIBS2)

%.x: %.o
	$(CC) -pthread -o $@ $< $(LDLIBS3)

sprawdzenie:
	diff -s magazyn.txt schowek.txt
clean:
	rm -f *.o *.x *.a *.so

shmemuse1.x: shmemuse.o libshmem.so
shmemuse2.x: shmemuse.o libshmem.so
glowny.x: glowny.o libsem.a libshmem.so
producent.x: producent.o libsem.a libshmem.so
konsument.x: konsument.o libsem.a libshmem.so