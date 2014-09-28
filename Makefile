CC = gcc
# add  -fdump-rtl-expand to the end of CFLAGS for further generating
# call graphs using `egypt'
CFLAGS = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes -Wuninitialized
OBJS = cricket.o utilities.o team.o engine.o analysis.o pitch.o commands.o misc.o

cricket: $(OBJS)
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -o cricket $(OBJS)

cricket.o: cricket.c cricket.h utilities.c utilities.h team.c team.h \
        engine.c engine.h analysis.c analysis.h \
        pitch.c pitch.h commands.c commands.h misc.c misc.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c cricket.c

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c utilities.c

team.o: team.c team.h fall_of_wickets.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c team.c

engine.o: engine.c engine.h analysis.o
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c engine.c

analysis.o: analysis.c analysis.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c analysis.c

pitch.o: pitch.c pitch.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c pitch.c

commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c commands.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c misc.c


# Tests
test: test-utilities test-engine

test-utilities: test-utilities.o utilities.o
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -o test-utilities test-utilities.o utilities.o

test-utilities.o: test-utilities.c test-utilities.h
	$(CC) $(CFLAGS) -std=c99 -pedantic -O -g -c test-utilities.c

test-utilities.h: test-utilities.c
	cproto test-utilities.c > test-utilities.h


clean:
	rm *.o cricket test-utilities