#ifndef PLAYER_H
#define PLAYER_H

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

#endif
