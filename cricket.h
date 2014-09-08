#ifndef CRICKET_H
#define CRICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct pitch_condition {
    int number;
    char *description;
} pitch_conditions [6] = {
    {1, "Hard and dry pitch.  Bowlers will perspire."},
    {2, "A very good wicket for batting."},
    {3, "Nice, even pitch.  Expect a fine balance."},
    {4, "Expect a good contest."},
    {5, "A bowler's paradise.  Runs will be hard to get."},
    {6, "Abandon hope, all ye that play here."}
};

int out_list [6] = {1, 2, 3, 4, 5, 6};
struct pitch_condition pitch;

void prepare_pitch (void);
int ball (int die1, int die2);
int one (void);
int two (void);
int three (void);
int four (void);
int wicket_chance (void);
int big_hit (void);
int extras (void);
int dot (void);


#endif
