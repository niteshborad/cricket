#include "team.h"
#include "analysis.h"
#include "pitch.h"
#include "misc.h"
#include "utilities.h"
#include "engine.h"
#include "analysis.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TOSS_DECISION_SIZE  6

/* Teams */
extern team *team_one;
extern team *team_two;
extern team *bat_team;
extern team *field_team;

/* Key players */
extern player *striker;
extern player *non_striker;
extern player *bowler;
extern player *non_bowler;
extern player *keeper;

/* Pitch */
extern pitch_condition pitch;
extern int out_list[6];

/* Match variables */
extern bool match_under_way;
extern bool innings_finished;
extern int max_overs;
extern int which_innings;
extern int target;


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


void swap_batsmen(void)
{
  player temp = *striker;
  *striker = *non_striker;
  *non_striker = temp;
}

void swap_bowlers(void)
{
  player temp = *bowler;
  *bowler = *non_bowler;
  *non_bowler = temp;
}

double calculate_strike_rate(player *batsman)
{
  return (double) batsman->runs_scored * 100 / batsman->balls;
}

void show_batsman_scoreline(player *batsman)
{
  printf("%s    %3d (%3d)  4s: %2d  6s: %2d  str: %5.2f\n",
	 batsman->name, batsman->runs_scored, batsman->balls,
	 batsman->fours, batsman->sixes, calculate_strike_rate(batsman));
}

double calculate_economy_rate(player *bowler)
{
  return (double) bowler->runs_conceded / bowler->overs;
}

void show_bowler_scoreline(player *bowler)
{
  printf("%s    %2d-%2d-%3d-%2d %4.2f\n",
	 bowler->name, bowler->overs, bowler->maidens,
	 bowler->runs_conceded, bowler->wickets, calculate_economy_rate(bowler));
}

void play_over(void)
{
  over();
  if (innings_finished)
  {
    return;
  }
  bat_team->overs++;
  bowler->overs++;
  if (bat_team->runs_in_over == 0)
  {
    bowler->maidens++;
    field_team->maidens++;
  }
  putchar('\n');

  show_batsman_scoreline(striker);
  show_batsman_scoreline(non_striker);
  putchar('\n');
  show_bowler_scoreline(bowler);
  show_bowler_scoreline(non_bowler);
  printf("This over: %d run%s\n", bat_team->runs_in_over, (bat_team->runs_in_over == 1) ? "" : "s");
  bat_team->runs_in_over = 0;
  bat_team->ball_ordinality = 0;
  scoreline(bat_team);

  swap_batsmen();

  bowler->overs++;
  swap_bowlers();
}

void over(void)
{
  int i;

  for (i = 0; i < 6; i++)
  {
    if (innings_finished) break;
    else play();
  }
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
  if (which_innings == 1 && innings_finished)
  {
    which_innings = 2;
    bat_team = team_two;
    field_team = team_one;
    innings_finished = false;
    striker = &bat_team->players[0];
    non_striker = &bat_team->players[1];
    change_aggression(striker->agg);
  }
  else
  {
    puts("The innings cannot be changed now");
  }
}

void try_new_match(void)
{
  if (match_under_way)
  {
    puts("There is already a match in progress.");

    bool got_answer = false;
    char answer = ' ';
    char ans_line[2];
    char *nl;
    while (!got_answer && (fputs("Stop the match? [y/n] ", stdout),
			   fgets(ans_line, 2, stdin) != NULL))
    {
      nl = strchr(ans_line, '\n');
      if (nl != NULL)
      {
	*nl = '\0';
      }
      getchar();
      answer = ans_line[0];
      switch (answer)
      {
      case 'y':
	match_under_way = false;
	got_answer = true;

	free(team_one->name);
	free(team_one);
	free(team_two->name);
	free(team_two);
	new_match();

	break;
      case 'n':
	got_answer = true;
	break;
      default:
	puts("Didn't get that.");
	break;
      }
    }
  }
  else
  {
    new_match();
  }
}

void new_match(void)
{
  team_one = make_team();
  team_two = make_team();
  prepare_pitch();
  get_team_names(team_one, team_two);

  char file_one[16], file_two[16];
  snprintf(file_one, 16, "teams/%s.txt", team_one->name);
  snprintf(file_two, 16, "teams/%s.txt", team_two->name);
  read_team_from_file(file_one, team_one);
  read_team_from_file(file_two, team_two);

  toss(team_one, team_two);
  match_under_way = true;
  striker = &bat_team->players[0];
  non_striker = &bat_team->players[1];
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
    {
      *nl = '\0';
    }
    if (lexcmp(decision, "bat") == 0)
    {
      team_one = winner;
      team_two = loser;
      break;
    }
    else if (lexcmp(decision, "bowl") == 0)
    {
      team_one = loser;
      team_two = winner;
      break;
    }
    else if (lexcmp(decision, "q") == 0 ||
	     lexcmp(decision, "quit") == 0)
    {
      quit();
    }
    else
    {
      puts("Only umpires can neither bat nor bowl.  Please choose again.");
      fputs("Bat or bowl? ", stdout);
    }
  }

  bat_team = team_one;
  field_team = team_two;
}

/*
 * Mechanics of deliveries
 */

void ball(int first_die, int second_die)
{
  if (bat_team->overs >= max_overs || bat_team->wickets >= bat_team->max_wickets)
  {
    innings_finished = true;
  }

  if (which_innings == 2 && bat_team->runs >= target)
  {
    innings_finished = true;
  }

  if (innings_finished)
  {
    if (which_innings == 1)
    {
      target = bat_team->runs + 1;
      puts("\tInnings over");
      scoreline(bat_team);
    }
    if (which_innings == 2)
    {
      puts("\tMatch over");
      match_under_way = false;
      summarize_match();

      free(team_one->name);
      free(team_two->name);
      free(team_one);
      free(team_two);

      exit(0);
    }
    return;
  }

  change_aggression(striker->agg);
  fprintf(stdout, "%s ", striker->name);
  if ((first_die == 1 && second_die == 1) ||
      (first_die == 1 && second_die == 2) ||
      (first_die == 2 && second_die == 1))
  {
    one();
  }
  else if (first_die == 2 && second_die == 2)
  {
    two();
  }
  else if (first_die == 3 && second_die == 3)
  {
    three_configuration();
  }
  else if (first_die == 4 && second_die == 4)
  {
    four();
  }
  else if (first_die == 5 && second_die == 5)
  {
    wicket_chance();
  }
  else if (first_die == 6 && second_die == 6)
  {
    big_hit();
  }
  else if (first_die == 1 && second_die == 4)
  {
    extras();
  }
  else
  {
    dot();
  }
}

void one(void)
{
  puts("1");
  striker->runs_scored += 1;
  striker->balls += 1;
  swap_batsmen();
  bat_team->runs += 1;
  bat_team->runs_in_over += 1;
  bat_team->partnership += 1;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded += 1;
}

void two(void)
{
  puts("2");
  striker->runs_scored += 2;
  striker->balls += 1;
  bat_team->runs += 2;
  bat_team->runs_in_over += 2;
  bat_team->partnership += 2;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded += 2;
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
  striker->runs_scored += 3;
  striker->balls += 1;
  swap_batsmen();
  bat_team->runs += 3;
  bat_team->runs_in_over += 3;
  bat_team->partnership += 3;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded += 3;
}

void four(void)
{
  puts("4");
  striker->runs_scored += 4;
  striker->balls += 1;
  striker->fours++;
  bat_team->fours++;
  bat_team->runs += 4;
  bat_team->runs_in_over += 4;
  bat_team->partnership += 4;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded += 4;
}

void six(void)
{
  puts("6");
  striker->runs_scored += 6;
  striker->balls += 1;
  striker->sixes++;
  bat_team->sixes++;
  bat_team->runs += 6;
  bat_team->runs_in_over += 6;
  bat_team->partnership += 6;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded += 6;
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

void wicket_chance(void)
{
  if (lookup(out_list, pitch.number, d6()))
  {
    mode_of_dismissal();
  }
  else
  {
    notout();
  }
}

void notout(void)
{
  puts("Not out");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
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

void set_fall_of_wickets(dismissal dismiss)
{
  fow *fall = &bat_team->fall_of_wickets[bat_team->wickets];

  fall->runs_at_fall = bat_team->runs;
  fall->overs_at_fall = bat_team->overs;
  fall->dismiss = dismiss;
  if (bat_team->ball_ordinality == 6)
  {
    fall->balls_into_over = 0;
  }
  else
  {
    fall->balls_into_over = bat_team->ball_ordinality;
  }

  striker->fall = *fall;
}

void caught_in_the_field(void)
{
  puts("Caught in the field");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bat_team->wickets++;
  set_fall_of_wickets(CAUGHT_FIELD);
  bowler->wickets++;
}

void caught_behind(void)
{
  puts("Caught behind");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bat_team->wickets++;
  set_fall_of_wickets(CAUGHT_BEHIND);
  bowler->wickets++;
}

void bowled(void)
{
  puts("Bowled");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bat_team->wickets++;
  set_fall_of_wickets(BOWLED);
  bowler->wickets++;
}

void lbw(void)
{
  puts("LBW");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bat_team->wickets++;
  set_fall_of_wickets(LBW);
  bowler->wickets++;
}

void runout(void)
{
  puts("Runout");
  striker->balls++;
  bat_team->wickets++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  set_fall_of_wickets(RUNOUT);
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
  striker->balls++;
  bat_team->wickets++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  set_fall_of_wickets(STUMPED);
  bowler->wickets++;
}

void hit_wicket(void)
{
  puts("Hit wicket");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bat_team->wickets++;
  set_fall_of_wickets(HIT_WICKET);
  bowler->wickets++;
}

void retired_hurt(void)
{
  puts("Retired hurt");
  striker->balls++;
  bat_team->max_wickets--;
  bat_team->partnership = 0;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  set_fall_of_wickets(RETD_HURT);
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
  bat_team->runs++;
  bat_team->runs_in_over++;
  bat_team->partnership++;
  bowler->wides++;
  field_team->wides++;
  ball(die1(), die2());
}

void leg_byes(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    puts("1 leg bye");
    bat_team->runs += 1;
    bat_team->runs_in_over += 1;
    bat_team->partnership += 1;
    field_team->legbyes += 1;
    break;
  case 3:
  case 4:
    puts("2 leg byes");
    bat_team->runs += 2;
    bat_team->runs_in_over += 2;
    bat_team->partnership += 2;
    field_team->legbyes += 2;
    break;
  case 5:
    puts("3 leg byes");
    bat_team->runs += 3;
    bat_team->runs_in_over += 3;
    bat_team->partnership += 3;
    field_team->legbyes += 3;
    break;
  case 6:
    puts("4 leg byes");
    bat_team->runs += 4;
    bat_team->runs_in_over += 4;
    bat_team->partnership += 4;
    field_team->legbyes += 4;
    break;
  }
  bat_team->balls++;
  bat_team->ball_ordinality++;
}

void byes(void)
{
  switch (d6())
  {
  case 1:
  case 2:
    puts("1 bye");
    bat_team->runs += 1;
    bat_team->runs_in_over += 1;
    bat_team->partnership += 1;
    field_team->byes += 1;
    break;
  case 3:
  case 4:
    puts("2 byes");
    bat_team->runs += 2;
    bat_team->runs_in_over += 2;
    bat_team->partnership += 2;
    field_team->byes += 2;
    break;
  case 5:
    puts("3 byes");
    bat_team->runs += 3;
    bat_team->runs_in_over += 3;
    bat_team->partnership += 3;
    field_team->byes += 3;
    break;
  case 6:
    puts("4 byes");
    bat_team->runs += 4;
    bat_team->runs_in_over += 4;
    bat_team->partnership += 4;
    field_team->byes += 4;
    break;
  }
  bat_team->balls++;
  bat_team->ball_ordinality++;
}

void noball(void)
{
  puts("No ball");
  bat_team->runs++;
  bat_team->runs_in_over++;
  bat_team->partnership++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
  bowler->runs_conceded++;
  field_team->noballs++;
  ball(die1(), die2());
}

void dot(void)
{
  puts("0");
  striker->balls++;
  bat_team->balls++;
  bat_team->ball_ordinality++;
}
