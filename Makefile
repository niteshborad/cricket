CC = ccache clang
# add  -fdump-rtl-expand to the end of CFLAGS for further generating
# call graphs using `egypt'
# CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings
CFLAGS = -Weverything -std=c99 -pedantic -O0 -g -pg
OBJS = cricket.o utilities.o team.o engine.o analysis.o pitch.o commands.o misc.o

cricket: $(OBJS)
	$(CC) $(CFLAGS) -o cricket $(OBJS)

cricket.o: cricket.c cricket.h utilities.c utilities.h team.c team.h \
        engine.c engine.h analysis.c analysis.h \
        pitch.c pitch.h commands.c commands.h misc.c misc.h
	$(CC) $(CFLAGS)  -c cricket.c

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS)  -c utilities.c

team.o: team.c team.h fall_of_wickets.h
	$(CC) $(CFLAGS)  -c team.c

engine.o: engine.c engine.h analysis.o
	$(CC) $(CFLAGS)  -c engine.c

analysis.o: analysis.c analysis.h
	$(CC) $(CFLAGS)  -c analysis.c

pitch.o: pitch.c pitch.h
	$(CC) $(CFLAGS)  -c pitch.c

commands.o: commands.c commands.h
	$(CC) $(CFLAGS)  -c commands.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS)  -c misc.c


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
