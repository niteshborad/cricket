#ifndef TEAM_H
#define TEAM_H

#define MAX_PLAYERS    11

/* Fall of wickets */
typedef struct
{
  int runs_at_fall;
  int overs_at_fall;
  int balls_into_over;
} fow;

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
} team;

team *make_team(void);
void get_team_names(team *a, team *b);
void init_fall_of_wickets(team *t);
void fall_of_wickets(team *t);

#endif
