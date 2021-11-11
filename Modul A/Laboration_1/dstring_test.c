#include <assert.h>
#include <string.h>

#include "dstring.h"

/* Detta program testar funktionaliteten for ADTn DString */
int main(void)
{
	DString str1, str2;
	str1 = dstring_initialize("Department of ");
	str2 = dstring_initialize("Redundancy ");
	int resultat = dstring_concatenate(&str1, str2); // Slar ihop str1 och str2 och lagger resultatet i str1. Str1 innehaller nu "Department of Redundancy"
    assert(resultat == 1); //det gick att allokera minne

	/* Om nagon av dessa misslyckas sa ar det nagot fel pa er implementation
	   Anvand debuggern for att ta reda pa vad */

	assert(str1 != NULL);
	assert(str2 != NULL);
	assert(strlen(str2) == 11); 
	assert(strlen(str1) == 25); // Den sammanslagna strangen ska ha langden 25

	/* Foljande ska skriva ut "Department of Redundancy Department" på skarmen
	   stdout ar en textfil som representerar konsollfonstret */

	dstring_print(str1, stdout);	// Skriver ut "Department of Redundancy" 
	dstring_truncate(&str1, 10);	// Forkortar str1 sa att den bara innehaller de 10 forsta tecknen i strangen, dvs "Department"
    assert(strlen(str1) == 10);
    assert(strlen(str2) == 11);
	dstring_print(str1, stdout);	// Skriver ut "Department"

	/* Frigor det dynamiskt allokerade minnet for strangarna */
	dstring_delete(&str1);
	dstring_delete(&str2);

	/* Se till att strangarna blivit nollstallda */
	assert(str1 == NULL);
	assert(str2 == NULL);
	return 0;
}
