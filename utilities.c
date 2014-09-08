#include "utilities.h"

int uniform_int_in (int min, int max)
/* Pick a number in [MIN, MAX] with uniform probability. */
{
    return min + (rand () / (RAND_MAX / max + 1));
}

void shuffle_int_array (int array [], int length)
/* Shuffle the integer array of the given length. */
{
    int i, j, temp;

    for (i = 0; i < length; i++) {
	j = rand () % (length - i);
	temp = array [i];
	array [i] = array [j];
	array [j] = temp;
    }
}    

bool lookup (int array [], size_t length, int key)
/* Search for KEY in ARRAY of size LENGTH.
 * Return true if found, else false.
 */
{
    size_t i;

    for (i = 0; i < length; i++)
	if (key == array [i])
	    return true;

    return false;
}    
