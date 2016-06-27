#include "team.h"
#include "analysis.h"

#include <stdio.h>
#include <stdbool.h>

/* Team */
extern team *bat_team;
extern team *field_team;
extern team *first;
extern team *second;
extern const int max_wickets;

/* Match variables */
extern bool innings_finished;
extern bool match_under_way;
extern int max_overs;
extern int which_innings;
extern int target;

/*
 * Match analysis
 */

double runrate(int runs, int overs)
{
  return ((double) runs) / overs;
}

void scoreline(team *t)
{
  printf("%-12s ", t->name);
  printf("Score: %d/%-2d    ", t->runs, t->wickets);
  printf("Overs: %d.%d    ", t->overs, t->ball_ordinality);
  if (t->overs > 0)
  {
    printf("Run rate: %.2f", runrate (t->runs, t->overs));
    if (match_under_way)
    {
      switch (which_innings)
      {
      case 1: putchar('\n');
	break;
      case 2: putchar(' ');
      }
      if (which_innings == 2)
	printf(" Run rate required: %.2f\n", (double) (target - t->runs) / (max_overs - t->overs));
    }
    else
    {
      putchar('\n');
    }
  }
  else
  {
    putchar('\n');
  }
}

void projected_score(team *t)
{
  if (t->overs > 0)
  {
    printf("Projected score: %d\n", (int) (t->runs + runrate(t->runs, t->overs) * (max_overs - t->overs)));
  }
}

int runs_in_boundaries(team *t)
{
  return t->fours * 4 + t->sixes * 6;
}

double percentage_runs_in_boundaries(team *t)
{
  if (t->runs == 0)
  {
    return 0;
  }
  return (double) (runs_in_boundaries(t) * 100) / t->runs;
}

void match_analysis(void)
{
  scoreline(bat_team);
  current_partnership();
  if (which_innings == 2)
  {
    printf("Target: %d    ", target);
    printf("Runs needed: %d    ", target - bat_team->runs);
    printf("   Run rate required: %.2f\n", (double) (target - bat_team->runs) / (max_overs - bat_team->overs));
  }
  printf("Fours: %d    Sixes: %d    ", bat_team->fours, bat_team->sixes);
  printf("Runs in boundaries: %d (%.1f%%)\n", runs_in_boundaries(bat_team), percentage_runs_in_boundaries(bat_team));
  printf("Maidens: %d\n", field_team->maidens);
  projected_score(bat_team);
}

void print_fall_of_wickets(void)
{
  fall_of_wickets(bat_team);
}

void current_partnership(void)
{
  fow last_fall = bat_team->fall_of_wickets[bat_team->wickets];
  int balls_until_last_wicket = last_fall.overs_at_fall * 6 + last_fall.balls_into_over;
  int balls_till_now = bat_team->overs * 6 + bat_team->ball_ordinality;
  int balls_for_current_partnership;

  if (bat_team->wickets == 0)
  {
    balls_for_current_partnership = bat_team->balls;
    last_fall.runs_at_fall = 0;
  }
  else
  {
    balls_for_current_partnership = balls_till_now - balls_until_last_wicket;
  }

  printf("Current partnership: %d runs off %d balls.\n", bat_team->runs - last_fall.runs_at_fall, balls_for_current_partnership);
}

void scorecard(void)
{
  scoreline(first);
  scoreline(second);
}

void summarize_match(void)
{
  scorecard();
  putchar('\n');
  if (first->runs > second->runs)
  {
    printf("%s win by %d runs\n", first->name, first->runs - second->runs);
  }
  else if (first->runs < second->runs)
  {
    printf("%s win by %d wickets\n", second->name, max_wickets - second->wickets);
  }
  else
  {
    puts("Match tied");
  }
}
