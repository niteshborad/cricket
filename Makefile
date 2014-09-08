cc = gcc

cricket: cricket.h cricket.c utilities.h utilities.c
	$(CC) $(CFLAGS) -std=c99 -pedantic -O0 -g -o cricket cricket.c utilities.c

clean:
	rm *.o cricket