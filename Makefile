CC = gcc
CFLAGS = -Wall -g

laba_3: main.o realise.o
	$(CC) $(CFLAGS) main.o realise.o -o laba_3

main.o: main.c golfile.h
	$(CC) $(CFLAGS) -c main.c -o main.o

realise.o: realise.c golfile.h
	$(CC) $(CFLAGS) -c realise.c -o realise.o

clean:
	rm -f *.o laba_3

