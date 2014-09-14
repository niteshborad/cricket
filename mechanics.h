#ifndef MECHANICS_H
#define MECHANICS_H

#include "team.h"
#include "analysis.h"
#include "engine.h"
#include "pitch.h"

/* Team */
extern team *t;

/* Engine */
extern int (*die1) (void);
extern int (*die2) (void);

/* Match variables */
extern bool innings_finished;
extern int max_overs;
extern int which_innings;
extern int target;

/* Pitch */
extern pitch_condition pitch;
extern int out_list [6];

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
