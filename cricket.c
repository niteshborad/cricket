/* A cricket simulator */

#include "cricket.h"
#include "utilities.h"

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
    
    /* if (t->overs >= max_overs || t->wickets >= max_wickets) { */
    /* 	innings_finished = true; */
    /* 	puts ("Innings over."); */
    /* 	scoreline (); */
    /* 	return; */
    /* } */
    t->overs++;
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
    which_innings = 2;
    t = second;
    nt = first;
    innings_finished = false;
    change_aggression (NORMAL);
}    

/*
 * Pitch
 */
void prepare_pitch (void)
{
    pitch = pitch_conditions [rand () % 6];
    shuffle_int_array (out_list, 6);
    pitch_condition ();
}

void pitch_condition (void)
{
    int i;
    for (i = 0; i < pitch.number; i++)
	printf ("%d ", out_list [i]);
    putchar ('\n');
    puts (pitch.description);
}    


/*
 * Mechanics of deliveries
 */

void ball (int die1, int die2)
{
    if (t->overs >= max_overs || t->wickets >= max_wickets)
	innings_finished = true;

    if (which_innings == 2 && t->runs >= target)
	innings_finished = true;

    if (innings_finished == true) {
	puts ("Innings over");
	scoreline (t);
	if (which_innings == 1)
	    target = t->runs + 1;
	return;
    }
       
    if ((die1 == 1 && die2 == 1) ||
	(die1 == 1 && die2 == 2) ||
	(die1 == 2 && die2 == 1))
	one ();
    else if (die1 == 2 && die2 == 2)
	two ();
    else if (die1 == 3 && die2 == 3)
	three ();
    else if (die1 == 4 && die2 == 4)
	four ();
    else if (die1 == 5 && die2 == 5)
	wicket_chance ();
    else if (die1 == 6 && die2 == 6)
	big_hit ();
    else if (die1 == 1 && die2 == 4)
	extras ();
    else
	dot ();
}    


void one (void)
{
    puts ("1");
    t->runs += 1;
    t->balls++;
    t->ball_ordinality++;
}

void two (void)
{
    puts ("2");
    t->runs += 2;
    t->balls++;
    t->ball_ordinality++;
}

void three_configuration (void)
{
    switch (d6()) {
    case 1:
    case 2:
	one ();
	break;
    case 3:
    case 4:
	two ();
	break;
    case 5:
	three ();
	break;
    case 6:
	four ();
	break;
    }
}

void three (void)
{    
    puts ("3");
    t->balls++;
    t->runs += 3;
    t->ball_ordinality++;
}

void four (void)
{
    puts ("4");
    t->balls++;
    t->runs += 4;
    t->fours++;
    t->ball_ordinality++;
}

void wicket_chance (void)
{
    if (lookup (out_list, pitch.number, d6()))
    	mode_of_dismissal ();
    else
	notout ();
}

void notout (void)
{
    puts ("Not out");
    t->balls++;
    t->ball_ordinality++;
}    

void mode_of_dismissal (void)
{
    switch (d10()) {
    case 1:
    case 2:
    case 3:
	puts ("Caught in the field");
	t->balls++;
	t->ball_ordinality++;
	t->wickets++;
	break;
    case 4:
    case 5:
	puts ("Caught behind");
	t->balls++;
	t->ball_ordinality++;
	t->wickets++;
	break;
    case 6:
    case 7:
	puts ("Bowled");
	t->balls++;
	t->ball_ordinality++;
	t->wickets++;
	break;
    case 8:
	puts ("LBW");
	t->balls++;
	t->ball_ordinality++;
	t->wickets++;
	break;
    case 9:
	puts ("Runout");
	t->balls++;
	t->ball_ordinality++;
	t->wickets++;
	break;
    case 10:
	puts ("Miscellany");
	break;
    }
}    

void big_hit (void)
{
    switch (d6()) {
    case 1:
    case 2:
    case 3:
    case 4:
	four ();
	break;
    case 5:
    case 6:
	six ();
	break;
    }
}

void six (void)
{
    puts ("6");
    t->runs += 6;
    t->balls++;
    t->sixes++;
    t->ball_ordinality++;
}

void extras (void)
{
    switch (d6()) {
    case 1:
	wide ();
	break;
    case 2:
    case 3:
	byes ();
	break;
    case 4:
    case 5:
	leg_byes ();
	break;
    case 6:
	noball ();
	break;
    }
}

void wide (void)
{
    puts ("Wide");
    t->runs++;
    ball (die1 (), die2 ());
}

void leg_byes (void)
{
    switch (d6()) {
    case 1:
    case 2:
	one ();
	break;
    case 3:
    case 4:
	two ();
	break;
    case 5:
	three ();
	break;
    case 6:
	four ();
	break;
    }
}

void byes (void)
{
    switch (d6()) {
    case 1:
    case 2:
	one ();
	break;
    case 3:
    case 4:
	two ();
	break;
    case 5:
	three ();
	break;
    case 6:
	four ();
	break;
    }
}    

void noball (void)
{
    puts ("No ball");
    t->runs++;
    t->balls++;
    t->ball_ordinality++;
    ball (die1 (), die2 ());
}    

void dot (void)
{
    puts ("0");
    t->balls++;
    t->ball_ordinality++;
}

/*
 * Match analysis
 */

double runrate (int runs, int overs)
{
    return ((double) runs) / overs;
}

void scoreline (team *t)
{
    printf ("%s    ", t->name);
    printf ("Score: %d/%d    ", t->runs, t->wickets);
    printf ("Overs: %d.%d    ", t->overs, t->ball_ordinality);
    printf ("Run rate: %.2f\n", runrate (t->runs, t->overs));
}

void projected_score (void)
{
    if (t->overs == 0)
	puts ("Play an over at least.");
    else
	printf ("Projected score: %d\n",
		(int) (t->runs + runrate (t->runs, t->overs) * (max_overs - t->overs)));
}    

void match_analysis (void)
{
    scoreline (t);
    if (which_innings == 2) {
	printf ("Target: %d    ", target);
	printf ("Runs needed: %d    ", target - t->runs);
	printf ("Run rate required: %.2f\n", (double) (target - t->runs) / (max_overs - t->overs));
    }
    printf ("Fours: %d    Sixes: %d\n", t->fours, t->sixes);
    projected_score ();
}    

void scorecard (void)
{
    scoreline (first);
    putchar ('\n');
    scoreline (second);
}    


int main (void)
{
    char line [6];
    char *nl;
    team foo = {
	"foo",
	0,
	0,
	0,
	0,
	0,
	0,
	0
    };
    team bar = {
	"bar",
	0,
	0,
	0,
	0,
	0,
	0,
	0
    };

    first = &foo;
    second = &bar;
    t = first;
    nt = second;
    
    srand ((unsigned) time (NULL));

    prepare_pitch ();
    while (fputs ("# ", stdout), fgets (line, 6, stdin) != NULL) {
	nl = strchr (line, '\n');
	if (nl != NULL)
	    *nl = '\0';
	if (strcmp (line, "o") == 0)
	    play_over ();
	else if (strcmp (line, "q") == 0)
	    return 1;
	else if (strcmp (line, "pc") == 0)
	    pitch_condition ();
	/* else if (strcmp (line, "ps") == 0) */
	/*     projected_score (); */
	else if (strcmp (line, "ma") == 0)
	    match_analysis ();
	else if (strcmp (line, "s") == 0) {
	    if (which_innings == 2 && innings_finished == true)
		scorecard ();
	    else
		scoreline (t);
	}
	else if (strcmp (line, "ci") == 0)
	    change_innings ();
	else if (strcmp (line, "c n") == 0)
	    change_aggression (NORMAL);
	else if (strcmp (line, "c a") == 0)
	    change_aggression (AGGRESSIVE);
	else if (strcmp (line, "c d") == 0)
	    change_aggression (DEFENSIVE);
	else if (strcmp (line, "c va") == 0)
	    change_aggression (VAGGRESSIVE);
	else if (strcmp (line, "c vd") == 0)
	    change_aggression (VDEFENSIVE);
	else
	    fputs ("Unknown command\n", stderr);
    }
	
    return 0;
}    
