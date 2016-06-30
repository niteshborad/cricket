#include "utilities.h"
#include "team.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_TEAM_NAME_SIZE     30
#define MAX_PLAYERS            11
#define MAX_WICKETS            10
#define TEAM_NAME_SIZE         64
#define PLAYER_NAME_SIZE       64

const int max_wickets = MAX_WICKETS;

/*
 * Teams
 */

player *make_player(void)
{
  player blank = {0};
  player *new_player = malloc(sizeof *new_player);
  if (new_player != NULL)
  {
    *new_player = blank;
  }
  return new_player;
}

void unmake_player(player *p)
{
  free(p->name);
  free(p);
}

team *make_team(void)		/* Due to Richard Heathfield */
{
  team blank = {0};
  team *new_team = malloc(sizeof *new_team);
  if (new_team != NULL)
  {
    *new_team = blank;
    new_team->max_wickets = MAX_WICKETS;
  }
  return new_team;
}

void unmake_team(team *t)
{
  free(t->name);
  free(t);
}

void get_team_names(team *a, team *b)
{
  char one[MAX_TEAM_NAME_SIZE], two[MAX_TEAM_NAME_SIZE];
  char *nl;
  /* bool found_newline_in_buffer = false; */
  size_t a_name_size, b_name_size;
  bool duplicate_names = false;

  do {
    puts("Enter the names of the teams playing on the next two lines.");
    puts("(Use only alphabets and digits, please.)");
    while (fputs("> ", stdout), fgets(one, MAX_TEAM_NAME_SIZE, stdin) != NULL)
    {
      nl = strchr(one, '\n');
      if (nl != NULL)
      {
	*nl = '\0';
	/* found_newline_in_buffer = true; */
      }
      else
      {
	/* found_newline_in_buffer = false; */
      }
      if (!alphabetic_numeric(one))
      {
	puts("Please use only alphabets and digits.");
	continue;
      }
      else
      {
	break;
      }
    }
    
    while (fputs("> ", stdout), fgets(two, MAX_TEAM_NAME_SIZE, stdin) != NULL)
    {
      nl = strchr(two, '\n');
      if (nl != NULL)
      {
	*nl = '\0';
	/* found_newline_in_buffer = true; */
      }
      else
      {
	/* found_newline_in_buffer = false; */
      }
      if (!alphabetic_numeric(two))
      {
	puts("Please use only alphabets and digits.");
	continue;
      }
      else
      {
	break;
      }
    }
    
    if (strcmp(one, two) != 0)
    {
      duplicate_names = false;
    }
    else
    {
      puts("A team playing against itself might be confusing.");
      puts("Please do not do that.");
      putchar('\n');
      duplicate_names = true;
    }
  } while (duplicate_names);


  errno = 0;
  a_name_size = strlen(one) + 1;
  a->name = malloc(a_name_size);
  if (a->name == NULL)
  {
    fprintf(stderr, "get_team_names: allocating space for a->name: %s\n", strerror(errno));
    exit(1);
  }
  strncpy(a->name, one, a_name_size - 1);
  a->name[a_name_size - 1] = '\0';

  errno = 0;
  b_name_size = strlen(two) + 1;
  b->name = malloc(b_name_size);
  if (b->name == NULL)
  {
    fprintf(stderr, "get_team_names: allocating space for b->name: %s\n", strerror(errno));
    exit(1);
  }
  strncpy(b->name, two, b_name_size - 1);
  b->name[b_name_size - 1] = '\0';
}

int read_line(char *line, size_t size, FILE *fp)
/* Read a line from file FP into buffer LINE of length SIZE. Drop the
 * newline.
 * Return 0 on success.
 * Return negative on failure.
 */
{
  if (fgets(line, size, fp) == NULL)
  {
    return -1;
  }

  char *nl = strchr(line, '\n');
  if (nl != NULL) *nl = '\0';

  return 0;
}

int read_team_from_file(char *file, team *t)
/* Try reading eleven names for team T from FILE.
 * Return 0 on success.
 * Return -1 if FILE could not be opened for reading.
 * Return -2 if there was an error reading from FILE.
 * Return -3 if memory could not be obtained.
 */
{
  FILE *fp;

  if ((fp = fopen(file, "r")) == NULL)
  {
    return -1;
  }

  char tm_line[TEAM_NAME_SIZE];
  errno = 0;
  if (read_line(tm_line, TEAM_NAME_SIZE, fp) < 0)
  {
    fprintf(stderr, "Error reading from '%s': %s\n", file, strerror(errno));
    fclose(fp);
    return -2;
  }
  t->name = malloc(sizeof *t->name * TEAM_NAME_SIZE);
  if (t->name == NULL) return -3;
  strncpy(t->name, tm_line, TEAM_NAME_SIZE);

  char pl_line[PLAYER_NAME_SIZE];
  int i;
  for (i = 0; i < MAX_PLAYERS; i++)
  {
    errno = 0;
    if (read_line(pl_line, PLAYER_NAME_SIZE, fp) < 0)
    {
      fprintf(stderr, "Error reading from '%s': %s\n", file, strerror(errno));
      fclose(fp);
      return -2;
    }
    t->players[i].name = malloc(sizeof *t->players[i].name * PLAYER_NAME_SIZE);
    if (t->players[i].name == NULL) return -3;
    strncpy(t->players[i].name, pl_line, PLAYER_NAME_SIZE);
  }

  fclose(fp);
  return 0;
}

void show_fall_of_wickets(team *t)
{
  int i;
  fow fall;

  if (t->wickets == 0)
  {
    puts("No wickets have fallen.");
    return;
  }

  /* Print half the list on one line */
  for (i = 1; i <= t->max_wickets / 2; i++)
  {
    fall = t->fall_of_wickets[i];
    if (fall.runs_at_fall == -1)
    {
      break;
    }
    printf("%d/%d ", fall.runs_at_fall, i);
    printf("(%d.%d)  ", fall.overs_at_fall, fall.balls_into_over);
  }
  putchar('\n');

  /* Print the other half on the next line */
  for ( ; i < t->max_wickets; i++)
  {
    fall = t->fall_of_wickets[i];
    if (fall.runs_at_fall == -1)
    {
      break;
    }
    printf("%d/%d ", fall.runs_at_fall, i);
    printf("(%d.%d)  ", fall.overs_at_fall, fall.balls_into_over);
  }
  putchar('\n');
}
