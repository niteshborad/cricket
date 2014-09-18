#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

#include "team.h"
#include "mechanics.h"
#include "analysis.h"
#include "pitch.h"

/* Team */
extern team *team_one;
extern team *team_two;
extern team *t;

/* Pitch */
extern pitch_condition pitch;

/* Engine */
typedef enum {
    VDEFENSIVE, DEFENSIVE, NORMAL, AGGRESSIVE, VAGGRESSIVE
} aggression;

/* Match variables */
extern bool match_under_way;
extern bool innings_finished;

int d6 (void);
int d8 (void);
int d10 (void);
void play2 (void);
void play4 (void);
void play6 (void);
void play8 (void);
void play10 (void);
void play_over (void);
void over (void);
void change_aggression (aggression agg);
void change_innings (void);
void new_match (void);
void toss (team *a, team *b);

/* Auxiliary */
void quit (void);

#endif
