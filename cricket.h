#ifndef CRICKET_H
#define CRICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

typedef enum {
    VDEFENSIVE, DEFENSIVE, NORMAL, AGGRESSIVE, VAGGRESSIVE
} aggression;

bool innings_finished = false;
bool match_under_way = false;
int which_innings = 1;
int max_overs = 50;

int target;
typedef struct {
    char *name;
    int overs;
    int balls;
    int ball_ordinality;
    int runs;
    int wickets;
    int fours;
    int sixes;
    int max_wickets;
} team;

team *first;
team *second;
team *t;
team *nt;

/* Teams */
team *make_team (char *name);
void toss (team *a, team *b);
void get_team_names (team *a, team *b);

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

/* Pitch */
void prepare_pitch (void);
void pitch_condition (void);

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

/* Match analysis */
double runrate (int runs, int overs);
void scoreline (team *t);
void projected_score (void);
void match_analysis (void);
void scorecard (void);

void new_match (team *a, team *b);
void help (void);

#endif
