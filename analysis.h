#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "team.h"

/* Match analysis */
double runrate(int runs, int overs);
void scoreline(team *t);
void projected_score(void);
int runs_in_boundaries(team *t);
double percentage_runs_in_boundaries(team *t);
void match_analysis(void);
void print_fall_of_wickets(void);
void current_partnership(void);
void scorecard(void);
void summarize_match(void);

#endif
