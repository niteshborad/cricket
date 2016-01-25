#include <assert.h>

#include "utilities.h"
#include "test-utilities.h"

/* bool alphabetic_numeric(const char *string); */
void alphabetic_numeric_empty(void)
{
  assert(alphabetic_numeric("") == true);
}

void alphabetic_numeric_single_alphabet(void)
{
  assert(alphabetic_numeric("x") == true);
}

void alphabetic_numeric_single_digit(void)
{
  assert(alphabetic_numeric("6") == true);
}

void alphabetic_numeric_single_space(void)
{
  assert(alphabetic_numeric(" ") == false);
}

void alphabetic_numeric_single_punctuator(void)
{
  assert(alphabetic_numeric("!") == false);
}

void alphabetic_numeric_mixed_spaces_digits(void)
{
  assert(alphabetic_numeric(" 1 2 3 4 5 6 7 8 9 ") == false);
}

void alphabetic_numeric_mixed_digits_spaces(void)
{
  assert(alphabetic_numeric("1 2 3 4 5 6 7 8 9") == false);
}

void alphabetic_numeric_mixed_letters_spaces(void)
{
  assert(alphabetic_numeric("a b c d e f g h i j k l m n o p q r s t u v w x y z") == false);
}

void alphabetic_numeric_mixed_spaces_letters(void)
{
  assert(alphabetic_numeric(" a b c d e f g h i j k l m n o p q r s t u v w x y z ") == false);
}

void alphabetic_numeric_characters_sampling(void)
{
  assert(alphabetic_numeric("!'a:@,oq#.ej$puk%yix^fdb&ghm*ctw{rnv}lsz/(-+)\\") == false);
}


/* bool lookup(int array[], size_t length, int key); */
void lookup_nonexisting_key(void)
{
  int array[5] = {1, 2, 3, 4, 5};
  assert(lookup(array, 5, 0) == false);
}

void lookup_existing_first_key(void)
{
  int array[5] = {1, 2, 3, 4, 5};
  assert(lookup(array, 5, 1) == true);
}

void lookup_existing_last_key(void)
{
  int array[5] = {1, 2, 3, 4, 5};
  assert(lookup(array, 5, 5) == true);
}

void lookup_existing_intermediate_key(void)
{
  int array[5] = {1, 2, 3, 4, 5};
  assert(lookup(array, 5, 4) == true);
}

void lookup_existing_double_key(void)
{
  int array[6] = {1, 2, 5, 3, 4, 5};
  assert(lookup(array, 6, 5) == true);
}


int main(void)
{
  /* bool alphabetic_numeric(const char *string); */
  alphabetic_numeric_empty();
  alphabetic_numeric_single_alphabet();
  alphabetic_numeric_single_digit();
  alphabetic_numeric_single_space();
  alphabetic_numeric_single_punctuator();
  alphabetic_numeric_mixed_spaces_digits();
  alphabetic_numeric_mixed_digits_spaces();
  alphabetic_numeric_mixed_letters_spaces();
  alphabetic_numeric_mixed_spaces_letters();
  alphabetic_numeric_characters_sampling();

  /* bool lookup(int array[], size_t length, int key); */
  lookup_nonexisting_key();
  lookup_existing_first_key();
  lookup_existing_last_key();
  lookup_existing_intermediate_key();
  lookup_existing_double_key();

  return 0;
}
