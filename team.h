#ifndef TEAM_H
#define TEAM_H

#include <stdbool.h>

#define MAX_PLAYERS    11

/* Fall of wickets */
typedef struct
{
  int runs_at_fall;
  int overs_at_fall;
  int balls_into_over;
} fow;

/* Players */
typedef struct
{
  char *name;
  int runs_scored;
  int balls;
  double strike_rate;
  int fours;
  int sixes;
  char *how_out;
  char *fow;
  int overs;
  int maidens;
  int runs_conceded;
  int wickets;
  double econ_rate;
  bool is_keeper;
} player;

/* Teams */
typedef struct
{
  char *name;
  int overs;
  fow fall_of_wickets[MAX_PLAYERS];
  int balls;
  int runs;
  int wickets;
  int fours;
  int sixes;
  int max_wickets;
  int maidens;
  int ball_ordinality;
  int runs_in_over;
  int partnership;
  player players[MAX_PLAYERS];
} team;

team *make_team(void);
void get_team_names(team *a, team *b);
void init_fall_of_wickets(team *t);
void print_fall_of_wickets(team *t);

#endif
