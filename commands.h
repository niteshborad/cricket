#ifndef COMMANDS_H
#define COMMANDS_H

#include "engine.h"

/* Commands */
typedef struct
{
    char *name;
    void (*do_it)(void);
} niladic;


typedef struct
{
    char *name;
    void (*set_aggression)(aggression aggr);
    aggression aggr;
} monadic;


niladic *lookup_niladic_command_name(char *command_name);
void do_niladic_unless_match_underway(niladic *command);
monadic *lookup_monadic_command_name(char *command_name);
void do_monadic_unless_match_underway(monadic *command);
void try_executing(char *command_name);

#endif
