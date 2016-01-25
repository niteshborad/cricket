#ifndef PITCH_H
#define PITCH_H

/* Pitch */
typedef struct
{
    int number;
    char *description;
} pitch_condition;

void prepare_pitch(void);
void show_pitch_condition(void);


#endif
