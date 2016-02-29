#include "utilities.h"
#include "pitch.h"

#include <stdio.h>
#include <stdlib.h>

pitch_condition pitch;

/*
 * Pitch
 */
pitch_condition pitch_conditions[6] =
{
     {1, "It's a hard and dry pitch.  The bowlers will perspire."},
     {2, "This looks like a very good wicket for batting."},
     {3, "A nice, even pitch.  Expect a fine balance."},
     {4, "There might be something for the bowlers.  Expect a good contest."},
     {5, "A bowler's paradise this.  Runs will be hard to get."},
     {6, "Abandon hope, all ye that play here."}
};

int out_list[6] = {1, 2, 3, 4, 5, 6};

void prepare_pitch(void)
{
     pitch = pitch_conditions[rand() % 6];
     shuffle_int_array(out_list, 6);
     show_pitch_condition();
}

void show_pitch_condition(void)
{
     /* int i; */
     /* for (i = 0; i < pitch.number; i++) */
     /* 	printf("%d ", out_list[i]); */
     /* putchar('\n'); */
     puts(pitch.description);
     putchar('\n');
}
