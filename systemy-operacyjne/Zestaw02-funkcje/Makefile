
CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:=
LDLIBS		:=



.PHONY: all clean

all: drzewko1.x drzewko2.x macierzysty.x potomny.x zombi.x orphan.x execute.x

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o *.x 

drzewko1.x: drzewko1.o procinfo.o
drzewko2.x: drzewko2.o procinfo.o
macierzysty.x: macierzysty.o procinfo.o
potomny.x: potomny.o procinfo.o
zombi.x: zombi.o
orphan.x: orphan.o
execute.x: execute.o
procinfo.o: procinfo.c procinfo.h
drzewko1.o: drzewko1.c procinfo.h
drzewko2.o: drzewko2.c procinfo.h
macierzysty.o: macierzysty.c procinfo.h
potomny.o: potomny.c procinfo.c
zombi.o: zombi.c
orphan.o: orphan.c
execute.o: execute.c