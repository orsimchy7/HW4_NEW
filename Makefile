CC=gcc
CFLAGS=-Wall -g -std=c99 -fpic
CLINK=$(CC)


libgrades.so: grades.o
	$(CLINK) -L. -shared grades.o -o libgrades.so -llinked-list


grades.o: grades.c grades.h
	$(CC) $(CFLAGS) -c grades.c




clean:
	rm -f libgrades.so grades.o 