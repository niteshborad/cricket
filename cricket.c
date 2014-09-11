/* A cricket simulator */

#include "cricket.h"
#include "utilities.h"


/*
 * Teams
 */
team *make_team (void)
{
    team *new_team;

    errno = 0;
    new_team = malloc (sizeof *new_team);
    if (new_team == NULL) {
	fprintf (stderr, "make_team: could not build a new team\n%s\n", strerror (errno));
	exit (1);
    }

    new_team->name = NULL;
    new_team->overs = 0;
    new_team->balls = 0;
    new_team->runs = 0;
    new_team->wickets = 0;
    new_team->fours = 0;
    new_team->sixes = 0;
    new_team->max_wickets = 10;
    new_team->maidens = 0;
    new_team->ball_ordinality = 0;
    new_team->runs_in_over = 0;

    return new_team;
}

void get_team_names (team *a, team *b)
{
    char *nl;
    char one [BUFSIZ], two [BUFSIZ];
    bool found_newline_in_buffer = false;
    size_t a_name_size, b_name_size;

    puts ("Enter the names of the teams playing on the next two lines.");
    puts ("(Use only alphabets and digits, please.)");
    while (fputs ("> ", stdout), fgets (one, BUFSIZ, stdin) != NULL) {
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
    
    while (fputs ("> ", stdout), fgets (two, BUFSIZ, stdin) != NULL) {
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
    prepare_pitch ();
    get_team_names (team_one, team_two);
    toss (team_one, team_two);
    match_under_way = true;
}

void toss (team *a, team *b)
{
    char *nl;
    char decision [6];
    team *winner, *loser;

    if (rand () % 2 == 0) {
	winner = a;
	loser = b;
    }
    else {
	winner = b;
	loser = a;
    }

    printf ("%s won the toss.  Bat or bowl? ", winner->name);
    while (true) {
	fgets (decision, 6, stdin);
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
    /* int i; */
    /* for (i = 0; i < pitch.number; i++) */
    /* 	printf ("%d ", out_list [i]); */
    /* putchar ('\n'); */
    puts (pitch.description);
}    


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
	runout ();
	break;
    case 10:
	miscellany ();
	break;
    }
}

void runout (void)
{
    puts ("Runout");
    t->wickets++;
    t->balls++;
    t->ball_ordinality++;
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
}    

void hit_wicket (void)
{
    puts ("Hit wicket");
    t->wickets++;
    t->balls++;
    t->ball_ordinality++;
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
    if (t->overs > 0)
	printf ("Run rate: %.2f\n", runrate (t->runs, t->overs));
    else
	putchar ('\n');
}

void projected_score (void)
{
    if (t->overs == 0)
	puts ("Play an over at least.");
    else
	printf ("Projected score: %d\n",
		(int) (t->runs + runrate (t->runs, t->overs) * (max_overs - t->overs)));
}    

int runs_in_boundaries (team *t)
{
    return (t->fours * 4 + t->sixes * 6);
}

double percentage_runs_in_boundaries (team *t)
{
    if (t->runs == 0)
	return 0;
    return (double) (runs_in_boundaries (t) * 100) / t->runs;
}    

void match_analysis (void)
{
    scoreline (t);
    if (which_innings == 2) {
	printf ("Target: %d    ", target);
	printf ("Runs needed: %d    ", target - t->runs);
	printf ("Run rate required: %.2f\n", (double) (target - t->runs) / (max_overs - t->overs));
    }
    printf ("Fours: %d    Sixes: %d    ", t->fours, t->sixes);
    printf ("Runs in boundaries: %d (%.1f%%)\n", runs_in_boundaries (t), percentage_runs_in_boundaries (t));
    printf ("Maidens: %d\n", nt->maidens);
    projected_score ();
}    

void scorecard (void)
{
    scoreline (first);
    putchar ('\n');
    scoreline (second);
}

void score (void)
{
    if (which_innings == 2 && innings_finished == true)
	scorecard ();
    else
	scoreline (t);
}


/*
 * Welcome and Help
 */
void welcome (void)
{
    puts ("\"It's not cricket.\"");
    puts ("A diminutive cricket simulator.");
    putchar ('\n');
    puts ("Type 'h' for some help.");
}    

void help (void)
{
    puts ("    At the prompt '#', you can type any of the following commands.");
    putchar ('\n');
    puts ("    If there is no match in progress:");
    puts ("q    - quit.");
    puts ("h    - get this help on usage.");
    puts ("nm   - begin a new match.");
    putchar ('\n');
    puts ("    If there is a match in progress:");
    puts ("o    - play the next over, unless the innings has ended.");
    puts ("pc   - tell something about the condition of the pitch.");
    puts ("ma   - analyze the situation in the current innings with some statistics.");
    puts ("s    - while the match is on, display the score for the team batting;");
    puts ("       will show the scorecards once the match has ended.");
    puts ("ci   - after the first innings completes, prepare for the next one.");
    puts ("c n  - play with a balance between attack and defence.");
    puts ("c a  - play aggressively while increasing the risk of wickets falling.");
    puts ("c va - play very aggressively while further increasing risk of wickets falling.");
    puts ("c d  - play defensively while decreasing the flow of runs.");
    puts ("c vd - play very defensively while further decreasing the flow of runs.");
    putchar ('\n');
    puts ("    No other commands will be recognized.");
}    


/*
 * Commands
 */
niladic *lookup_niladic_command_name (char *command_name)
{
    niladic *np;
    for (np = niladic_commands; np->name != NULL; np++)
	if (strcmp (command_name, np->name) == 0)
	    return np;
    return NULL;
}

void do_niladic_unless_match_underway (niladic *command)
{
    if (match_under_way == true)
	command->do_it();
    else
	puts ("There is no match in progress yet.");
}    

monadic *lookup_monadic_command_name (char *command_name)
{
    monadic *mp;
    for (mp = monadic_commands; mp->name != NULL; mp++)
	if (strcmp (command_name, mp->name) == 0)
	    return mp;
    return NULL;
}

void do_monadic_unless_match_underway (monadic *command)
{
    if (match_under_way == true)
	command->set_aggression (command->aggr);
    else
	puts ("There is no match in progress yet.");
}

void try_executing (char *command_name)
{
    niladic *ncmd;
    monadic *mcmd;

    if (strcmp ("nm", command_name) == 0 ||
	strcmp ("q", command_name) == 0 ||
	strcmp ("h", command_name) == 0)
	lookup_niladic_command_name (command_name)->do_it ();

    else if ((ncmd = lookup_niladic_command_name (command_name)) != NULL)
	do_niladic_unless_match_underway (ncmd);
    else if ((mcmd = lookup_monadic_command_name (command_name)) != NULL)
	do_monadic_unless_match_underway (mcmd);
    else
	puts ("Unknown command.  Press 'h' for some help.");
}


/*
 * Auxiliary
 */
void quit (void)
{
    exit (0);
}


/* Main return codes:
 * 0 - successful exit
 * 1 - error allocating memory
 */
int main (void)
{
    char line [6];
    char *nl;

    srand ((unsigned) time (NULL));

    team_one = make_team ();
    team_two = make_team ();

    welcome ();
    while (fputs ("# ", stdout), fgets (line, 6, stdin) != NULL) {
	nl = strchr (line, '\n');
	if (nl != NULL)
	    *nl = '\0';
	try_executing (line);
    }
	
    return 0;
}    
