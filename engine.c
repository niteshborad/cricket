#include "utilities.h"
#include "engine.h"
#include "analysis.h"

#define MAX_TOSS_DECISION_SIZE  6

/*
 * Engine
 */
int d6(void)
{
  return uniform_int_in(1, 6);
}

int d8(void)
{
  return uniform_int_in(1, 8);
}

int d10(void)
{
  return uniform_int_in(1, 10);
}

static int (*die1) (void) = d6;
static int (*die2) (void) = d6;


void play2(void)
{
  int roll_on_die2 = die2();
  die2 = d10;

  switch (roll_on_die2)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    ball(die1(), roll_on_die2);
    break;
  case 7:
  case 8:
  case 9:
  case 10:
    dot();
    break;
  }
}

void play4(void)
{
  int roll_on_die2 = die2();
  die2 = d8;

  switch (roll_on_die2)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    ball(die1(), roll_on_die2);
    break;
  case 7:
  case 8:
    dot();
    break;
  }
}

void play6(void)
{
  die2 = d6;
  ball(die1(), die2());
}

void play8(void)
{
  int roll_on_die2 = die2();
  int roll;
  die2 = d8;
    
  switch (roll_on_die2)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    ball(die1(), roll_on_die2);
    break;
  case 7:
  case 8:
    roll = die1();
    ball(roll, roll);
    break;
  }
}

void play10(void)
{
  int roll_on_die2 = die2();
  int roll;
  die2 = d10;
    
  switch (roll_on_die2)
  {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
    ball(die1(), roll_on_die2);
    break;
  case 7:
  case 8:
  case 9:
  case 10:
    roll = die1();
    ball(roll, roll);
    break;
  }
}

static void (*play) (void) = play6;


void play_over(void)
{
  over();
  if (innings_finished == true)
    return;
  t->overs++;
  if (t->runs_in_over == 0)
    nt->maidens++;
  putchar('\n');
  printf("This over: %d run%s\n", t->runs_in_over, (t->runs_in_over == 1) ? "" : "s");
  /* fputs ("Current partnership: ", stdout); */
  /* current_partnership (); */
  t->runs_in_over = 0;
  t->ball_ordinality = 0;
  scoreline(t);
}

void over(void)
{
  int i;

  for (i = 0; i < 6; i++)
    if (innings_finished == false)
      play();
    else
      break;
}    

void change_aggression(aggression agg)
{
  switch (agg)
  {
  case VDEFENSIVE:
    die2 = d10;
    play = play2;
    break;
  case DEFENSIVE:
    die2 = d8;
    play = play4;
    break;
  case NORMAL:
    die2 = d6;
    play = play6;
    break;
  case AGGRESSIVE:
    die2 = d8;
    play = play8;
    break;
  case VAGGRESSIVE:
    die2 = d10;
    play = play10;
    break;
  }
}    

void change_innings(void)
{
  if (which_innings == 1 && innings_finished == true)
  {
    which_innings = 2;
    t = second;
    nt = first;
    innings_finished = false;
    change_aggression(NORMAL);
  }
  else
    puts("The innings cannot be changed now");
}    

void new_match()
{
  team_one = make_team();
  team_two = make_team();
  prepare_pitch();
  get_team_names(team_one, team_two);
  toss(team_one, team_two);
  match_under_way = true;
}

void toss(team *a, team *b)
{
  char *nl;
  char decision[MAX_TOSS_DECISION_SIZE];
  team *winner, *loser;

  if (rand() % 2 == 0)
  {
    winner = a;
    loser = b;
  }
  else
  {
    winner = b;
    loser = a;
  }

  printf("%s won the toss.  Bat or bowl? ('q' to quit) ", winner->name);
  while (true)
  {
    fgets(decision, MAX_TOSS_DECISION_SIZE, stdin);
    nl = strchr(decision, '\n');
    if (nl != NULL)
      *nl = '\0';
    if (lexcmp(decision, "bat") == 0)
    {
      first = winner;
      second = loser;
      break;
    }
    else if (lexcmp(decision, "bowl") == 0)
    {
      first = loser;
      second = winner;
      break;
    }
    else if (lexcmp(decision, "q") == 0 ||
	     lexcmp(decision, "quit") == 0)
      quit();
    else
    {
      puts("Only umpires can neither bat nor bowl.  Please choose again.");
      fputs("Bat or bowl? ", stdout);
    }
  }

  t = first;
  nt = second;
}    

/*
 * Mechanics of deliveries
 */

void ball(int first_die, int second_die)
{
  if (t->overs >= max_overs || t->wickets >= t->max_wickets)
    innings_finished = true;

  if (which_innings == 2 && t->runs >= target)
    innings_finished = true;
    
  if (innings_finished == true)
  {
    if (which_innings == 1)
    {
      target = t->runs + 1;
      puts("\tInnings over");
      scoreline(t);
    }
    if (which_innings == 2)
    {
      puts("\tMatch over");
      summarize_match();
      match_under_way = false;
      /* innings_finished = false; */
      exit(0);
    }
    return;
  }

  if ((first_die == 1 && second_die == 1) ||
      (first_die == 1 && second_die == 2) ||
      (first_die == 2 && second_die == 1))
    one();
  else if (first_die == 2 && second_die == 2)
    two();
  else if (first_die == 3 && second_die == 3)
    three_configuration();
  else if (first_die == 4 && second_die == 4)
    four();
  else if (first_die == 5 && second_die == 5)
    wicket_chance();
  else if (first_die == 6 && second_die == 6)
    big_hit();
  else if (first_die == 1 && second_die == 4)
    extras();
  else
    dot();
}    


void one(void)
{
  puts("1");
  t->runs += 1;
  t->runs_in_over += 1;
  t->partnership += 1;
  t->balls++;
  t->ball_ordinality++;
}

void two(void)
{
  puts("2");
  t->runs += 2;
  t->runs_in_over += 2;
  t->partnership += 2;
  t->balls++;
  t->ball_ordinality++;
}

void three_configuration(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    one();
    break;
  case 3:
  case 4:
    two();
    break;
  case 5:
    three();
    break;
  case 6:
    four();
    break;
  }
}

void three(void)
{    
  puts("3");
  t->runs += 3;
  t->runs_in_over += 3;
  t->partnership += 3;
  t->balls++;
  t->ball_ordinality++;
}

void four(void)
{
  puts("4");
  t->fours++;
  t->runs += 4;
  t->runs_in_over += 4;
  t->partnership += 4;
  t->balls++;
  t->ball_ordinality++;
}

void wicket_chance(void)
{
  if (lookup(out_list, pitch.number, d6()))
    mode_of_dismissal();
  else
    notout();
}

void notout(void)
{
  puts("Not out");
  t->balls++;
  t->ball_ordinality++;
}    

void mode_of_dismissal(void)
{
  switch (d10()){
  case 1:
  case 2:
  case 3:
    caught_in_the_field();
    break;
  case 4:
  case 5:
    caught_behind();
    break;
  case 6:
  case 7:
    bowled();
    break;
  case 8:
    lbw();
    break;
  case 9:
    runout();
    break;
  case 10:
    miscellany();
    break;
  }
}

void set_fall_of_wickets(team *t)
{
  fow *fall = &(t->fall_of_wickets[t->wickets]);
    
  fall->runs_at_fall = t->runs;
  fall->overs_at_fall = t->overs;
  fall->balls_into_over = t->ball_ordinality;
}    

void caught_in_the_field(void)
{
  puts("Caught in the field");
  t->balls++;
  t->ball_ordinality++;
  t->wickets++;
  set_fall_of_wickets(t);
}    

void caught_behind(void)
{
  puts("Caught behind");
  t->balls++;
  t->ball_ordinality++;
  t->wickets++;
  set_fall_of_wickets(t);
}

void bowled(void)
{
  puts("Bowled");
  t->balls++;
  t->ball_ordinality++;
  t->wickets++;
  set_fall_of_wickets(t);
}

void lbw(void)
{
  puts("LBW");
  t->balls++;
  t->ball_ordinality++;
  t->wickets++;
  set_fall_of_wickets(t);
}    

void runout(void)
{
  puts("Runout");
  t->wickets++;
  t->balls++;
  t->ball_ordinality++;
  set_fall_of_wickets(t);
}

void miscellany(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    runout();
    break;
  case 3:
  case 4:
    stumped();
    break;
  case 5:
    hit_wicket();
    break;
  case 6:
    retired_hurt();
    break;
  }
}    

void stumped(void)
{
  puts("Stumped");
  t->wickets++;
  t->balls++;
  t->ball_ordinality++;
  set_fall_of_wickets(t);
}    

void hit_wicket(void)
{
  puts("Hit wicket");
  t->balls++;
  t->ball_ordinality++; 
  t->wickets++;
  set_fall_of_wickets(t);
}

void retired_hurt(void)
{
  puts("Retired hurt");
  t->max_wickets--;
  t->partnership = 0;
  t->balls++;
  t->ball_ordinality++;
}    

void big_hit(void)
{
  switch (d6())
  {
  case 1:
  case 2:
  case 3:
  case 4:
    four();
    break;
  case 5:
  case 6:
    six();
    break;
  }
}

void six(void)
{
  puts("6");
  t->sixes++;
  t->runs += 6;
  t->runs_in_over += 6;
  t->partnership += 6;
  t->balls++;
  t->ball_ordinality++;
}

void extras(void)
{
  switch (d6())
  {
  case 1:
    wide();
    break;
  case 2:
  case 3:
    byes();
    break;
  case 4:
  case 5:
    leg_byes();
    break;
  case 6:
    noball();
    break;
  }
}

void wide(void)
{
  puts("Wide");
  t->runs++;
  t->runs_in_over++;
  t->partnership++;
  ball(die1(), die2());
}

void leg_byes(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    puts("1 leg bye");
    t->runs += 1;
    t->runs_in_over += 1;
    t->partnership += 1;
    break;
  case 3:
  case 4:
    puts("2 leg byes");
    t->runs += 2;
    t->runs_in_over += 2;
    t->partnership += 2;
    break;
  case 5:
    puts("3 leg byes");
    t->runs += 3;
    t->runs_in_over += 3;
    t->partnership += 3;
    break;
  case 6:
    puts("4 leg byes");
    t->runs += 4;
    t->runs_in_over += 4;
    t->partnership += 4;	
    break;
  }
}

void byes(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    puts("1 bye");
    t->runs += 1;
    t->runs_in_over += 1;
    t->partnership += 1;
    break;
  case 3:
  case 4:
    puts("2 byes");
    t->runs += 2;
    t->runs_in_over += 2;
    t->partnership += 2;
    break;
  case 5:
    puts("3 byes");
    t->runs += 3;
    t->runs_in_over += 3;
    t->partnership += 3;
    break;
  case 6:
    puts("4 byes");
    t->runs += 4;
    t->runs_in_over += 4;
    t->partnership += 4;
    break;
  }
}    

void noball(void)
{
  puts("No ball");
  t->runs++;
  t->runs_in_over++;
  t->partnership++;
  t->balls++;
  t->ball_ordinality++;
  ball(die1(), die2());
}    

void dot(void)
{
  puts("0");
  t->balls++;
  t->ball_ordinality++;
}
