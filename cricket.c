/* A cricket simulator */

#include "team.h"
#include "engine.h"
#include "analysis.h"
#include "pitch.h"
#include "commands.h"
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#define CMDLINESIZE    6

/* Teams */
/* These hold the states of the teams */
team *team_one;
team *team_two;
/* These deciding the order of play */
team *first;
team *second;
/* In an innings, t is the team batting, nt is the one bowling */
team *t;
team *nt;

extern const int max_players;

/* Match variables */
bool innings_finished = false;
bool match_under_way = false;
int which_innings = 1;
int max_overs = 50;
int target;

/* Pitch */
extern pitch_condition pitch;

int main(void)
/* Exit codes:
 * 0 - successful exit
 * 1 - error allocating memory
 */
{
  srand((unsigned) time(0));

  char line[CMDLINESIZE];
  char *nl;

  welcome();
  while (fputs("# ", stdout), fgets(line, CMDLINESIZE, stdin) != NULL)
  {
    nl = strchr(line, '\n');
    if (nl != NULL)
    {
      *nl = '\0';
    }
    putchar('\n');
    try_executing(line);
  }

  return 0;
}
