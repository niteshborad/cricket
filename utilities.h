#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdbool.h>

int uniform_int_in (int min, int max);
void shuffle_int_array (int array [], int length);
bool lookup (int array [], size_t length, int key);

#endif
