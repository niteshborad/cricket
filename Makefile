CC = gcc
# add  -fdump-rtl-expand to the end of CFLAGS for further generating
# call graphs using `egypt'
CFLAGS = -std=c89 -pedantic-errors -Wall -Wextra -Werror -Og -g

OBJS = cricket.o utilities.o team.o engine.o analysis.o pitch.o commands.o misc.o
# Headers generated with     echo *.h
HEADERS = analysis.h commands.h cricket.h engine.h fall_of_wickets.h misc.h pitch.h team.h utilities.h


cricket: $(OBJS) $(HEADERS) depend
	$(CC) $(CFLAGS) -o cricket $(OBJS)

depend:
	$(CC) $(CFLAGS) -E -MM *.c > .depend

include .depend


# Tests
test: test-utilities test-engine

test-utilities: test-utilities.o utilities.o
	$(CC) $(CFLAGS)  -o test-utilities test-utilities.o utilities.o

test-utilities.o: test-utilities.c test-utilities.h
	$(CC) $(CFLAGS)  -c test-utilities.c

test-utilities.h: test-utilities.c
	cproto test-utilities.c > test-utilities.h


clean:
	rm -f *.o cricket test-utilities
