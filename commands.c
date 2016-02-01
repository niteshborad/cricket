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
  {"nm", new_match},
  {"ma", match_analysis},
  {"cp", current_partnership},
  {"fow", print_fall_of_wickets},
  {"pc", show_pitch_condition},
  {"ci", change_innings},
  {NULL, NULL}
};

monadic monadic_commands[] =
{
  {"c n", change_aggression, NORMAL},
  {"c a", change_aggression, AGGRESSIVE},
  {"c d", change_aggression, DEFENSIVE},
  {"c va", change_aggression, VAGGRESSIVE},
  {"c vd", change_aggression, VDEFENSIVE},
  {NULL, NULL, -1}
};

niladic *lookup_niladic_command_name(char *command_name)
{
  niladic *np;
  for (np = niladic_commands; np->name != NULL; np++)
    if (strcmp (command_name, np->name) == 0)
      return np;
  return NULL;
}

void do_niladic_unless_match_underway(niladic *command)
{
  if (match_under_way)
    command->do_it();
  else
    puts("There is no match in progress yet.");
}

monadic *lookup_monadic_command_name(char *command_name)
{
  monadic *mp;
  for (mp = monadic_commands; mp->name != NULL; mp++)
    if (strcmp (command_name, mp->name) == 0)
      return mp;
  return NULL;
}

void do_monadic_unless_match_underway(monadic *command)
{
  if (match_under_way)
    command->set_aggression(command->aggr);
  else
    puts("There is no match in progress yet.");
}

void try_executing(char *command_name)
{
  niladic *ncmd;
  monadic *mcmd;

  if (strcmp("nm", command_name) == 0 ||
      strcmp("q", command_name) == 0 ||
      strcmp("h", command_name) == 0)
    lookup_niladic_command_name(command_name)->do_it();
  else if ((ncmd = lookup_niladic_command_name(command_name)) != NULL)
    do_niladic_unless_match_underway(ncmd);
  else if ((mcmd = lookup_monadic_command_name(command_name)) != NULL)
    do_monadic_unless_match_underway(mcmd);
  else
    puts("Unknown command.  Press 'h' for some help.");
}
