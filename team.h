#ifndef TEAM_H
#define TEAM_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_PLAYERS     11
#define DISMISSAL_SIZE 100

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
  char how_out[DISMISSAL_SIZE];
  dismissal dismiss;
} fow;

/* Players */
typedef struct
{
  char *name;
  aggression agg;
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

player *make_player(void);
void unmake_player(player *p);
team *make_team(void);
void unmake_team(team *t);
void get_team_names(team *a, team *b);
int read_line(char *line, size_t size, FILE *fp);
int read_team_from_file(char *file, team *t);
void show_fall_of_wickets(team *t);

#endif
