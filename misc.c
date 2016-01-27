#include "misc.h"

#include <stdio.h>
#include <stdlib.h>


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
  exit(0);
}
