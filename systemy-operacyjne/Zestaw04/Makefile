CC			:= gcc
CFLAGS		:= -Wall -O3 -std=c99
LDFLAGS		:= 
LDLIBS		:= 


.PHONY: all clean

all: prodkons.x

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f *.o *.x *.a 

prodkons.x: prodkons.o
prodkons.o: prodkons.c