cc = gcc

cricket: cricket.h cricket.o utilities.h utilities.o
	$(CC) $(CFLAGS) -std=c99 -pedantic -O0 -g -o cricket cricket.o utilities.o

depend:  
	$(CC) $(CFLAGS) -E -MM *.c > .depend

clean:
	rm *.o cricket interface.tab.c