#ifndef TEAM_H
#define TEAM_H

#include <stdbool.h>

#define MAX_PLAYERS    11

/* Batting aggression */
typedef enum
{
  VDEFENSIVE, DEFENSIVE, NORMAL, AGGRESSIVE, VAGGRESSIVE
} aggression;

/* Dismissal modes */
typedef enum
{
  CAUGHT_FIELD, CAUGHT_BEHIND, BOWLED, LBW, RUNOUT, STUMPED, HIT_WICKET, RETD_HURT
} dismissal;

/* Fall of wickets */
typedef struct
{
  int runs_at_fall;
  int overs_at_fall;
  int balls_into_over;
  char *how_out;
  dismissal dismiss;
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
  fow fall;
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
int read_team_from_file(FILE *fp);
void show_fall_of_wickets(team *t);

#endif
