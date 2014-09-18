#include "utilities.h"
#include "engine.h"

#define MAX_TOSS_DECISION_SIZE  6

/*
 * Engine
 */
int d6 (void)
{
    return uniform_int_in (1, 6);
}

int d8 (void)
{
    return uniform_int_in (1, 8);
}

int d10 (void)
{
    return uniform_int_in (1, 10);
}

int (*die1) (void) = d6;
int (*die2) (void) = d6;


void play2 (void)
{
    int roll_on_die2 = die2 ();
    die2 = d10;

    switch (roll_on_die2) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
	ball (die1 (), roll_on_die2);
	break;
    case 7:
    case 8:
    case 9:
    case 10:
	dot ();
	break;
    }
}

void play4 (void)
{
    int roll_on_die2 = die2 ();
    die2 = d8;

    switch (roll_on_die2) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
	ball (die1 (), roll_on_die2);
	break;
    case 7:
    case 8:
	dot ();
	break;
    }
}

void play6 (void)
{
    die2 = d6;
    ball (die1 (), die2 ());
}

void play8 (void)
{
    int roll_on_die2 = die2 ();
    int roll;
    die2 = d8;
    
    switch (roll_on_die2) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
	ball (die1 (), roll_on_die2);
	break;
    case 7:
    case 8:
	roll = die1 ();
	ball (roll, roll);
	break;
    }
}

void play10 (void)
{
    int roll_on_die2 = die2 ();
    int roll;
    die2 = d10;
    
    switch (roll_on_die2) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
	ball (die1 (), roll_on_die2);
	break;
    case 7:
    case 8:
    case 9:
    case 10:
	roll = die1 ();
	ball (roll, roll);
	break;
    }
}

void (*play) (void) = play6;


void play_over (void)
{
    over ();
    if (innings_finished == true)
	return;
    t->overs++;
    if (t->runs_in_over == 0)
	nt->maidens++;
    t->runs_in_over = 0;
    t->ball_ordinality = 0;
    scoreline (t);
}

void over (void)
{
    int i;

    for (i = 0; i < 6; i++)
	if (innings_finished == false)
	    play ();
	else
	    break;
}    

void change_aggression (aggression agg)
{
    switch (agg) {
    case VDEFENSIVE:
	die2 = d10;
	play = play2;
	break;
    case DEFENSIVE:
	die2 = d8;
	play = play4;
	break;
    case NORMAL:
	die2 = d6;
	play = play6;
	break;
    case AGGRESSIVE:
	die2 = d8;
	play = play8;
	break;
    case VAGGRESSIVE:
	die2 = d10;
	play = play10;
	break;
    }
}    

void change_innings (void)
{
    if (which_innings == 1 && innings_finished == true) {
	which_innings = 2;
	t = second;
	nt = first;
	innings_finished = false;
	change_aggression (NORMAL);
    }
    else
	puts ("The innings cannot be changed now");
}    

void new_match ()
{
    team_one = make_team ();
    team_two = make_team ();
    prepare_pitch ();
    get_team_names (team_one, team_two);
    toss (team_one, team_two);
    match_under_way = true;
}

void toss (team *a, team *b)
{
    char *nl;
    char decision [MAX_TOSS_DECISION_SIZE];
    team *winner, *loser;

    if (rand () % 2 == 0) {
	winner = a;
	loser = b;
    }
    else {
	winner = b;
	loser = a;
    }

    printf ("%s won the toss.  Bat or bowl? ('q' to quit) ", winner->name);
    while (true) {
	fgets (decision, MAX_TOSS_DECISION_SIZE, stdin);
	nl = strchr (decision, '\n');
	if (nl != NULL)
	    *nl = '\0';
	if (lexcmp (decision, "bat") == 0) {
	    first = winner;
	    second = loser;
	    break;
	}
	else if (lexcmp (decision, "bowl") == 0) {
	    first = loser;
	    second = winner;
	    break;
	}
	else if (lexcmp (decision, "q") == 0 ||
		 lexcmp (decision, "quit") == 0)
	    quit ();
	else {
	    puts ("Only umpires can neither bat nor bowl.  Please choose again.");
	    fputs ("Bat or bowl? ", stdout);
	}
    }

    t = first;
    nt = second;
}    

/*
 * Auxiliary
 */
void quit (void)
{
    exit (0);
}
