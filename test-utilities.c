#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "utilities.h"
#include "test-utilities.h"

#define NDEBUG

/* bool alphabetic_numeric (const char *string); */
void alphabetic_numeric_empty (void)
{
    assert (alphabetic_numeric ("") == true);
}    

void alphabetic_numeric_single_alphabet (void)
{
    assert (alphabetic_numeric ("x") == true);
}

void alphabetic_numeric_single_digit (void)
{
    assert (alphabetic_numeric ("6") == true);
}    

void alphabetic_numeric_single_space (void)
{
    assert (alphabetic_numeric (" ") == false);
}    

void alphabetic_numeric_single_punctuator (void)
{
    assert (alphabetic_numeric ("!") == false);
}

void alphabetic_numeric_mixed_spaces_digits (void)
{
    assert (alphabetic_numeric (" 1 2 3 4 5 6 7 8 9 ") == false);
}    

void alphabetic_numeric_mixed_digits_spaces (void)
{
    assert (alphabetic_numeric ("1 2 3 4 5 6 7 8 9") == false);
}    

void alphabetic_numeric_mixed_letters_spaces (void)
{
    assert (alphabetic_numeric ("a b c d e f g h i j k l m n o p q r s t u v w x y z") == false);
}

void alphabetic_numeric_mixed_spaces_letters (void)
{
    assert (alphabetic_numeric (" a b c d e f g h i j k l m n o p q r s t u v w x y z ") == false);
}

void alphabetic_numeric_characters_sampling (void)
{
    assert (alphabetic_numeric ("!'a:@,oq#.ej$puk%yix^fdb&ghm*ctw{rnv}lsz/(-+)\\") == false);
}    


int main (void)
{
    /* bool alphabetic_numeric (const char *string); */
    alphabetic_numeric_empty ();
    alphabetic_numeric_single_alphabet ();
    alphabetic_numeric_single_digit ();
    alphabetic_numeric_single_space ();
    alphabetic_numeric_single_punctuator ();
    alphabetic_numeric_mixed_spaces_digits ();
    alphabetic_numeric_mixed_digits_spaces ();
    alphabetic_numeric_mixed_letters_spaces ();
    alphabetic_numeric_mixed_spaces_letters ();
    alphabetic_numeric_characters_sampling ();

    return 0;
}    
