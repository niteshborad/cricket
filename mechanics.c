#include "utilities.h"
#include "mechanics.h"

/*
 * Mechanics of deliveries
 */

void ball (int die1, int die2)
{
    if (t->overs >= max_overs || t->wickets >= t->max_wickets)
	innings_finished = true;

    if (which_innings == 2 && t->runs >= target)
	innings_finished = true;
    
    if (innings_finished == true) {
	puts ("\tInnings over");
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
	three_configuration ();
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
    t->runs_in_over += 1;
    t->balls++;
    t->ball_ordinality++;
}

void two (void)
{
    puts ("2");
    t->runs += 2;
    t->runs_in_over += 2;
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
    t->runs += 3;
    t->runs_in_over += 3;
    t->balls++;
    t->ball_ordinality++;
}

void four (void)
{
    puts ("4");
    t->fours++;
    t->runs += 4;
    t->runs_in_over += 4;
    t->balls++;
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
	caught_in_the_field ();
	break;
    case 4:
    case 5:
	caught_behind ();
	break;
    case 6:
    case 7:
	bowled ();
	break;
    case 8:
	lbw ();
	break;
    case 9:
	runout ();
	break;
    case 10:
	miscellany ();
	break;
    }
}

void set_fall_of_wickets (team *t)
{
    fow *fall = &(t->fall_of_wickets [t->wickets]);
    
    fall->runs_at_fall = t->runs;
    fall->overs_at_fall = t->overs;
    fall->balls_into_over = t->ball_ordinality;
}    

void caught_in_the_field (void)
{
    puts ("Caught in the field");
    t->balls++;
    t->ball_ordinality++;
    t->wickets++;
    set_fall_of_wickets (t);
}    

void caught_behind (void)
{
    puts ("Caught behind");
    t->balls++;
    t->ball_ordinality++;
    t->wickets++;
    set_fall_of_wickets (t);
}

void bowled (void)
{
    puts ("Bowled");
    t->balls++;
    t->ball_ordinality++;
    t->wickets++;
    set_fall_of_wickets (t);
}

void lbw (void)
{
    puts ("LBW");
    t->balls++;
    t->ball_ordinality++;
    t->wickets++;
    set_fall_of_wickets (t);
}    

void runout (void)
{
    puts ("Runout");
    t->wickets++;
    t->balls++;
    t->ball_ordinality++;
    set_fall_of_wickets (t);
}

void miscellany (void)
{
    switch (d6()) {
    case 1:
    case 2:
	runout ();
	break;
    case 3:
    case 4:
	stumped ();
	break;
    case 5:
	hit_wicket ();
	break;
    case 6:
	retired_hurt ();
	break;
    }
}    

void stumped (void)
{
    puts ("Stumped");
    t->wickets++;
    t->balls++;
    t->ball_ordinality++;
    set_fall_of_wickets (t);
}    

void hit_wicket (void)
{
    puts ("Hit wicket");
    t->balls++;
    t->ball_ordinality++; 
    t->wickets++;
    set_fall_of_wickets (t);
}

void retired_hurt (void)
{
    puts ("Retired hurt");
    t->max_wickets--;
    t->balls++;
    t->ball_ordinality++;
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
    t->sixes++;
    t->runs += 6;
    t->runs_in_over += 6;
    t->balls++;
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
    t->runs_in_over++;
    ball (die1 (), die2 ());
}

void leg_byes (void)
{
    switch (d6()) {
    case 1:
    case 2:
	puts ("1 leg bye");
	break;
    case 3:
    case 4:
	puts ("2 leg byes");
	break;
    case 5:
	puts ("3 leg byes");
	break;
    case 6:
	puts ("4 leg byes");
	break;
    }
}

void byes (void)
{
    switch (d6()) {
    case 1:
    case 2:
	puts ("1 bye");
	break;
    case 3:
    case 4:
	puts ("2 byes");
	break;
    case 5:
	puts ("3 byes");
	break;
    case 6:
	puts ("4 byes");
	break;
    }
}    

void noball (void)
{
    puts ("No ball");
    t->runs++;
    t->runs_in_over++;
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
