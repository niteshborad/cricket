#include "commands.h"
#include "team.h"
#include "engine.h"
#include "analysis.h"
#include "misc.h"
#include "pitch.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Team */
extern team *first;
extern team *second;
extern const int max_wickets;


extern bool match_under_way;

/*
 * Commands
 */
niladic niladic_commands[] =
{
  {"o", play_over},
  {"q", quit},
  {"h", help},
  {"nm", try_new_match},
  {"ma", match_analysis},
  {"cp", current_partnership},
  {"fow", print_fall_of_wickets},
  {"pc", show_pitch_condition},
  {"ci", change_innings},
  {"c n", change_aggression_normal},
  {"c a", change_aggression_aggressive},
  {"c d", change_aggression_defensive},
  {"c va", change_aggression_very_aggressive},
  {"c vd", change_aggression_very_defensive},
  {"sb", set_bowler},
  {NULL, NULL}
};

niladic *lookup_niladic_command_name(char *command_name)
{
  niladic *np;
  for (np = niladic_commands; np->name != NULL; np++)
  {
    if (strcmp(command_name, np->name) == 0)
    {
      return np;
    }
  }
  return NULL;
}

void do_niladic_unless_match_underway(niladic *command)
{
  if (match_under_way)
  {
    command->do_it();
  }
  else
  {
    puts("There is no match in progress yet.");
  }
}

void try_executing(char *command_name)
{
  niladic *ncmd;
  
  if (strcmp("nm", command_name) == 0 ||
      strcmp("q", command_name) == 0 ||
      strcmp("h", command_name) == 0)
  {
    lookup_niladic_command_name(command_name)->do_it();
  }
  else if ((ncmd = lookup_niladic_command_name(command_name)) != NULL)
  {
    do_niladic_unless_match_underway(ncmd);
  }
  else
  {
    puts("Unknown command.  Press 'h' for some help.");
  }
}
