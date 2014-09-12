#ifndef CRICKET_H
#define CRICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PLAYERS    11

const int max_players = MAX_PLAYERS;

/* Fall of wickets */
typedef struct {
    int runs_at_fall;
    int overs_at_fall;
    int balls_into_over;
} fow;


/* Teams */
typedef struct {
    char *name;
    int overs;
    fow fall_of_wickets [MAX_PLAYERS];
    int balls;
    int runs;
    int wickets;
    int fours;
    int sixes;
    int max_wickets;
    int maidens;
    int ball_ordinality;
    int runs_in_over;
} team;

team *make_team (void);
void get_team_names (team *a, team *b);
void init_fall_of_wickets (team *t);
void fall_of_wickets (team *t);

/* For getting data */
team *team_one;
team *team_two;
/* Deciding the order of play */
team *first;
team *second;
/* In an innings, t is the team batting, nt is the one bowling */
team *t;
team *nt;



/* Engine */
typedef enum {
    VDEFENSIVE, DEFENSIVE, NORMAL, AGGRESSIVE, VAGGRESSIVE
} aggression;

bool innings_finished = false;
bool match_under_way = false;
int which_innings = 1;
int max_overs = 50;

int target;

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


/* Pitch */
struct pitch_condition {
    int number;
    char *description;
} pitch_conditions [6] = {
    {1, "It's a hard and dry pitch.  The bowlers will perspire."},
    {2, "This looks like a very good wicket for batting."},
    {3, "A nice, even pitch.  Expect a fine balance."},
    {4, "There might be something for the bowlers.  Expect a good contest."},
    {5, "A bowler's paradise this.  Runs will be hard to get."},
    {6, "Abandon hope, all ye that play here."}
};

struct pitch_condition pitch;
int out_list [6] = {1, 2, 3, 4, 5, 6};

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


/* Match analysis */
double runrate (int runs, int overs);
void scoreline (team *t);
void projected_score (void);
int runs_in_boundaries (team *t);
double percentage_runs_in_boundaries (team *t);
void match_analysis (void);
void print_fall_of_wickets (void);
void current_partership (void);
void scorecard (void);
void score (void);


/* Welcome and Help */
void welcome (void);
void help (void);


/* Auxiliary */
void quit (void);


/* Commands */
typedef struct {
    char *name;
    void (*do_it) (void);
} niladic;

niladic niladic_commands [] = {
    {"o", play_over},
    {"q", quit},
    {"h", help},
    {"nm", new_match},
    {"ma", match_analysis},
    {"s", score},
    {"cp", current_partership},
    {"fow", print_fall_of_wickets},
    {"pc", pitch_condition},
    {"ci", change_innings},
    {NULL, NULL}
};

niladic *lookup_niladic_command_name (char *command_name);
void do_niladic_unless_match_underway (niladic *command);

typedef struct {
    char *name;
    void (*set_aggression) (aggression aggr);
    aggression aggr;
} monadic;

monadic monadic_commands [] = {
    {"c n", change_aggression, NORMAL},
    {"c a", change_aggression, AGGRESSIVE},
    {"c d", change_aggression, DEFENSIVE},
    {"c va", change_aggression, VAGGRESSIVE},
    {"c vd", change_aggression, VDEFENSIVE},
    {NULL, NULL, -1}
};

monadic *lookup_monadic_command_name (char *command_name);
void do_monadic_unless_match_underway (monadic *command);

void try_executing (char *command_name);

#endif
