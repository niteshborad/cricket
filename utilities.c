/* Parts copyright (c) 1991-2000 iMatix Corporation.
 * lexcmp based on the original by iMatix Corporation, obtained from
 * <http://legacy.imatix.com/html/sfl/>
 * Modified and used under the rights granted by
 * The SFL License Agreement
 * <http://legacy.imatix.com/html/sfl/sfl4.htm#license>
 */

#include "utilities.h"

#include <ctype.h>

int uniform_int_in(int min, int max)
/* Pick a number in [MIN, MAX] with uniform probability, where
 *             0 <= min <= max <= 32767
 * Adapted from randrange() by Richard Heathfield.
 */
{
  if (min > max)
  {
    int t = min; min = max; max = t;
  }
  if (!(0 <= min && max <= 32767))
    return -1;
  return min + (max - min + 1) * (rand() / (RAND_MAX + 1.0));
}

void shuffle_int_array(int array[], int length)
/* Shuffle the integer array of the given length.
 * NOTE: can only deal with arrays of maximum length 32768 on
 *       account of the RNG.
 */
{
  int i, j, temp;

  for (i = 0; i < length; i++)
  {
    j = uniform_int_in(i, length - 1);
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

bool lookup(int array[], size_t length, int key)
/* Search for KEY in ARRAY of size LENGTH.
 * Return true if found, else false.
 */
{
  size_t i;

  for (i = 0; i < length; i++)
    if (key == array[i])
      return true;

  return false;
}

bool alphabetic_numeric(const char *string)
/* Is the given string made up only of alphabetic and/or numeric
 * characters?
 */
{
  const char *sp;

  for (sp = string; *sp != '\0'; sp++)
    if (!isalnum(*sp))
      return false;
  return true;
}


/*  */
/*  ---------------------------------------------------------------------[<]-
    Function: lexcmp

    Synopsis: Performs an unsigned comparison of two strings without regard
    to the case of any letters in the strings.  Returns a value that is
    <TABLE>
    <_0     if string1 is less than string2
    ==_0    if string1 is equal to string2
    >_0     if string1 is greater than string2
    </TABLE>
    ---------------------------------------------------------------------[>]-*/

int lexcmp (const char *string1, const char *string2)
{
  int cmp;

  do
  {
    cmp = (unsigned char) tolower (*string1) - (unsigned char) tolower (*string2);
  }
  while (*string1++ && *string2++ && cmp == 0);
  return (cmp);
}
