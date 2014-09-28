/* A cricket simulator */

#include "utilities.h"
#include "cricket.h"

/* Main return codes:
 * 0 - successful exit
 * 1 - error allocating memory
 */
int main (void)
{
    char line [6];
    char *nl;

    srand ((unsigned) time (NULL));

    welcome ();
    while (fputs ("# ", stdout), fgets (line, 6, stdin) != NULL) {
	nl = strchr (line, '\n');
	if (nl != NULL)
	    *nl = '\0';
	putchar ('\n');
	try_executing (line);
    }
	
    return 0;
}    
