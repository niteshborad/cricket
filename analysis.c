#include "analysis.h"

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

void print_fall_of_wickets (void)
{
    fall_of_wickets (t);
}    

void current_partnership (void)
{
    fow last_fall = t->fall_of_wickets [t->wickets];
    int balls_until_last_wicket = last_fall.overs_at_fall * 6 + last_fall.balls_into_over;
    int balls_since_last_wicket = t->overs * 6 + t->ball_ordinality;
    int balls_for_current_partnership;

    if (t->wickets == 0)
	balls_for_current_partnership = t->balls;
    else
	balls_for_current_partnership = balls_since_last_wicket - balls_until_last_wicket;
    
    printf ("%d runs off %d balls.\n", t->runs - last_fall.runs_at_fall, balls_for_current_partnership);
}    

void scorecard (void)
{
    scoreline (first);
    scoreline (second);
}

void summarize_match (void)
{
    scorecard ();
    putchar ('\n');
    if (first->runs > second->runs)
        printf ("%s win by %d runs\n", first->name, first->runs - second->runs);
    else if (first->runs < second->runs)
        printf ("%s win by %d wickets\n", second->name, max_wickets - second->wickets);
    else
        puts ("Match tied");
}    
