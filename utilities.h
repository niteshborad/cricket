/* Parts copyright (c) 1991-2000 iMatix Corporation.
 * lexcmp based on the original by iMatix Corporation, obtained from
 * <http://legacy.imatix.com/html/sfl/>
 * Modified and used under the rights granted by
 * The SFL License Agreement
 * <http://legacy.imatix.com/html/sfl/sfl4.htm#license>
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdbool.h>

unsigned long int random_number();
int uniform_int_in(int min, int max);
void shuffle_int_array(int array[], int length);
bool lookup(int array[], size_t length, int key);
bool alphabetic_numeric(const char *string);

/* Based on the original by iMatix Corporation (c) 1991-2000 */
int lexcmp(const char *string1, const char *string2);

#endif
