#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

#include "team.h"
#include "analysis.h"
#include "pitch.h"

/* Team */
extern team *team_one;
extern team *team_two;
extern team *t;

/* Pitch */
extern pitch_condition pitch;
extern int out_list [6];

/* Engine */
typedef enum {
    VDEFENSIVE, DEFENSIVE, NORMAL, AGGRESSIVE, VAGGRESSIVE
} aggression;

/* Match variables */
extern bool match_under_way;
extern bool innings_finished;
extern int max_overs;
extern int which_innings;
extern int target;


/* Engine */
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

/* Mechanics */
void ball (int die1, int die2);
void one (void);
void two (void);
void three_configuration (void);
void three (void);
void four (void);
void wicket_chance (void);
void notout (void);
void mode_of_dismissal (void);
void set_fall_of_wickets (team *t);
void caught_in_the_field (void);
void caught_behind (void);
void bowled (void);
void lbw (void);
void runout (void);
void miscellany (void);
void stumped (void);
void hit_wicket (void);
void retired_hurt (void);
void big_hit (void);
void six (void);
void extras (void);
void wide (void);
void byes (void);
void leg_byes (void);
void noball (void);
void dot (void);

#endif
