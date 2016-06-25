CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -Wextra -Werror -Og -g3 -fsanitize=undefined -fsanitize=address -fsanitize=leak -fsanitize=bounds-strict
OBJS = analysis.o commands.o cricket.o engine.o misc.o pitch.o team.o utilities.o
HEADERS = analysis.h commands.h engine.h misc.h pitch.h team.h utilities.h

cricket: $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -o cricket $(OBJS)

depend: 
	$(CC) $(CFLAGS) -E -MM *.c > .depend

include .depend

tags: 
	etags *.[ch] > TAGS

clean: 
	rm -f *.o cricket
