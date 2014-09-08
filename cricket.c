/* A cricket simulator */

#include "cricket.h"
#include "utilities.h"

#define d6() (uniform_int_in (1, 6))
#define d8() (uniform_int_in (1, 8))
#define d10() (uniform_int_in (1, 10))

void prepare_pitch (void)
{
    int i;
    pitch = pitch_conditions [rand () % 6];

    shuffle_int_array (out_list, 6);
    for (i = 0; i < pitch.number; i++)
	printf ("%d ", out_list [i]);
    putchar ('\n');
    puts (pitch.description);
}

/*
 * Core
 */

int ball (int die1, int die2)
{
    int outcome;

    /* This switch-case replaces a long series of if-else-if conditions
     * on the two dice by use of a hack: summing the dice.  This results
     * in unique values for for all conditions and thus can be cased.
     */
    switch (die1 + die2) {
    case 2:
	outcome = one ();
	break;
    case 3:
	outcome = one ();
	break;
    case 4:
	outcome = two ();
	break;
    case 6:
	outcome = three ();
	break;
    case 8:
	outcome = four ();
	break;
    case 10:
	outcome = wicket_chance ();
	break;
    case 12:
	outcome = big_hit ();
	break;
    case 5:
	outcome = extras ();
	break;
    default:
	outcome = dot ();
	break;
    }
    return outcome;
}    

/*
  (dolist (func '(one two three four wicket_chance big_hit extras dot))
  (insert (format "int %s (void);\n" (symbol-name func)))
  (insert (format "int %s (void)\n" (symbol-name func)))
  (insert (format "{\n\n}\n"))
  (newline))
*/

int one (void)
{
    return 1;
}

int two (void)
{
    return 2;
}

int three (void)
{
    int outcome;
    
    switch (d6()) {
    case 1:
    case 2:
	outcome = 1;
	break;
    case 3:
    case 4:
	outcome = 2;
	break;
    case 5:
	outcome = 3;
	break;
    case 6:
	outcome = 4;
	break;
    }
    return outcome;
}

int four (void)
{
    return 4;
}

int wicket_chance (void)
{
    /* if (lookup (out_list, d6)()) */
    /* 	mode_of_dismissal (); */
    return 0;
}

int big_hit (void)
{
    int outcome;
    
    switch (d6()) {
    case 1:
    case 2:
    case 3:
    case 4:
	outcome = 4;
	break;
    case 5:
    case 6:
	outcome = 6;
	break;
    }
    return outcome;
}

int extras (void)
{
    return 5;
}

int dot (void)
{
    return 0;
}

int main (void)
{
    int i;
    
    srand ((unsigned) time (NULL));

    for (i = 0; i < 6; i++)
	printf ("%d\n", ball (d6(), d6()));
    
    return 0;
}    
