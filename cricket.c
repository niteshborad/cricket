/* A cricket simulator */

#include "cricket.h"
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


/* Team */
/* For getting data */
team *team_one;
team *team_two;
/* Deciding the order of play */
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

/* Main return codes:
 * 0 - successful exit
 * 1 - error allocating memory
 */
int main(void)
{
  char line[6];
  char *nl;

  srand((unsigned) time(0));

  welcome();
  while (fputs("# ", stdout), fgets(line, 6, stdin) != NULL)
  {
    nl = strchr(line, '\n');
    if (nl != NULL)
      *nl = '\0';
    putchar('\n');
    try_executing(line);
  }

  return 0;
}
