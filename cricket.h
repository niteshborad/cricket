#ifndef CRICKET_H
#define CRICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#include "team.h"
#include "engine.h"
#include "analysis.h"
#include "pitch.h"
#include "commands.h"
#include "misc.h"

/* Team */
/* For getting data */
team *team_one;
team *team_two;
/* Deciding the order of play */
team *first;
team *second;
/* In an innings, t is the team batting, nt is the one bowling */
team *t;
team *nt;

extern const int max_players;

/* Pitch */
extern pitch_condition pitch;

/* Match variables */
bool innings_finished = false;
bool match_under_way = false;
int which_innings = 1;
int max_overs = 50;
int target;

/* Engine */
extern int (*die1) (void);
extern int (*die2) (void);



#endif
