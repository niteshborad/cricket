#include "misc.h"
#include "team.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Match variables */
extern bool match_under_way;

/* Team */
extern team *team_one;
extern team *team_two;
extern team *t;
extern team *nt;
extern team *first;
extern team *second;

/*
 * Miscellaneous
 */
void welcome(void)
{
  puts("\"It's not cricket.\"");
  puts("A diminutive cricket simulator.");
  putchar ('\n');
  puts("Type 'h' for some help.");
}

void help(void)
{
  puts("    At the prompt '#', you can type any of the following commands.");
  putchar('\n');
  puts("    If there is no match in progress:");
  puts("q    - quit.");
  puts("h    - get this help on usage.");
  puts("nm   - begin a new match.");
  putchar('\n');
  puts("    If there is a match in progress:");
  puts("o    - play the next over, unless the innings has ended.");
  puts("pc   - tell something about the condition of the pitch.");
  puts("ma   - analyze the situation in the current innings with some statistics.");
  puts("fow  - show the fall of wickets.");
  puts("cp   - show the current partnership.");
  puts("ci   - after the first innings completes, prepare for the next one.");
  puts("c n  - play with a balance between attack and defence.");
  puts("c a  - play aggressively while increasing the risk of wickets falling.");
  puts("c va - play very aggressively while further increasing risk of wickets falling.");
  puts("c d  - play defensively while decreasing the flow of runs.");
  puts("c vd - play very defensively while further decreasing the flow of runs.");
  putchar('\n');
  puts("    No other commands will be recognized.");
}

void quit(void)
{
  match_under_way = false;

  if (team_one)
  {
    free(team_one->name);
    free(team_one);
  }
  if (team_one)
  {
    free(team_two->name);
    free(team_two);
  }

  exit(0);
}
