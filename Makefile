CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wuninitialized

cricket: cricket.h cricket.o utilities.h utilities.o
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -o cricket cricket.o utilities.o

cricket.o: cricket.c cricket.h utilities.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c cricket.c

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c utilities.c

clean:
	rm *.o cricket interface.tab.c