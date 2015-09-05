#ifndef PITCH_H
#define PITCH_H

#include <stdio.h>
#include <stdlib.h>

/* Pitch */
typedef struct
{
    int number;
    char *description;
} pitch_condition;

pitch_condition pitch;

void prepare_pitch(void);
void show_pitch_condition(void);


#endif
