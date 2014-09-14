#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "team.h"

/* Team */
extern team *t;
extern team *nt;
extern team *first;
extern team *second;

/* Match variables */
extern bool innings_finished;
extern int max_overs;
extern int which_innings;
extern int target;

/* Match analysis */
double runrate (int runs, int overs);
void scoreline (team *t);
void projected_score (void);
int runs_in_boundaries (team *t);
double percentage_runs_in_boundaries (team *t);
void match_analysis (void);
void print_fall_of_wickets (void);
void current_partership (void);
void scorecard (void);
void score (void);

#endif
