#include "utilities.h"
#include "team.h"

#define MAX_TEAM_NAME_SIZE     30

/*
 * Teams
 */
team *make_team (void)		/* Due to Richard Heathfield */
{
    team blank = {0};
    team *new_team = malloc (sizeof *new_team);
    if (new_team != NULL) {
	*new_team = blank;
	new_team->max_wickets = 10;
	init_fall_of_wickets (new_team);
    }
    return new_team;
}

void get_team_names (team *a, team *b)
{
    char one [MAX_TEAM_NAME_SIZE], two [MAX_TEAM_NAME_SIZE];
    char *nl;
    bool found_newline_in_buffer = false;
    size_t a_name_size, b_name_size;
    bool duplicate_names = false;

    do {
	puts ("Enter the names of the teams playing on the next two lines.");
	puts ("(Use only alphabets and digits, please.)");
	while (fputs ("> ", stdout), fgets (one, MAX_TEAM_NAME_SIZE, stdin) != NULL) {
	    nl = strchr (one, '\n');
	    if (nl != NULL) {
		*nl = '\0';
		found_newline_in_buffer = true;
	    }
	    else
		found_newline_in_buffer = false;
	    if (alphabetic_numeric (one) == false) {
		puts ("Please use only alphabets and digits.");
		continue;
	    }
	    else
		break;
	}
	if (found_newline_in_buffer == false)
	    while (getchar () != '\n')
		;
    
	while (fputs ("> ", stdout), fgets (two, MAX_TEAM_NAME_SIZE, stdin) != NULL) {
	    nl = strchr (two, '\n');
	    if (nl != NULL) {
		*nl = '\0';
		found_newline_in_buffer = true;
	    }
	    else
		found_newline_in_buffer = false;
	    if (alphabetic_numeric (two) == false) {
		puts ("Please use only alphabets and digits.");
		continue;
	    }
	    else
		break;
	}
	if (found_newline_in_buffer == false)
	    while (getchar () != '\n')
		;

	if (strcmp (one, two) != 0)
	    duplicate_names = false;
	else {
	    puts ("A team playing against itself might be confusing.");
	    puts ("Please do not do that.");
	    putchar ('\n');
	    duplicate_names = true;
	}
    } while (duplicate_names == true);

    
    errno = 0;
    a_name_size = strlen (one) + 1;
    a->name = malloc (a_name_size);
    if (a->name == NULL) {
	fprintf (stderr, "get_team_names: allocating space for a->name: %s\n", strerror (errno));
	exit (1);
    }
    strncpy (a->name, one, a_name_size - 1);
    a->name [a_name_size - 1] = '\0';

    errno = 0;
    b_name_size = strlen (two) + 1;
    b->name = malloc (b_name_size);
    if (b->name == NULL) {
	fprintf (stderr, "get_team_names: allocating space for b->name: %s\n", strerror (errno));
	exit (1);
    }
    strncpy (b->name, two, b_name_size - 1);
    b->name [b_name_size - 1] = '\0';
}

void init_fall_of_wickets (team *t)
{
    int i;

    for (i = 1; i < max_players; i++)
	t->fall_of_wickets [i].runs_at_fall = -1;
}

void fall_of_wickets (team *t)
{
    int i;
    fow fall;
    
    if (t->wickets == 0) {
	puts ("No wickets have fallen.");
	return;
    }

    /* Print half the list on one line */
    for (i = 1; i <= t->max_wickets / 2; i++) {
	fall = t->fall_of_wickets [i];
	if (fall.runs_at_fall == -1)
	    break;
	printf ("%d/%d ", fall.runs_at_fall, i);
	printf ("(%d.%d)  ", fall.overs_at_fall, fall.balls_into_over);
    }
    putchar ('\n');

    /* Print the other half on the next line */
    for ( ; i < t->max_wickets; i++) {
	fall = t->fall_of_wickets [i];
	if (fall.runs_at_fall == -1)
	    break;
	printf ("%d/%d ", fall.runs_at_fall, i);
	printf ("(%d.%d)  ", fall.overs_at_fall, fall.balls_into_over);
    }
    putchar ('\n');
}    
