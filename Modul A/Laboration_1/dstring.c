#define _CRT_SECURE_NO_WARNINGS
#include "dstring.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


DString dstring_initialize(const char* str)
{
	// Precondition: str ar ej NULL
	assert(str != NULL);

	int charAmount = strlen(str) + 1;

	DString temp = (DString)malloc(charAmount * sizeof(char));

	if (temp != NULL) {
		strcpy(temp, str);
		return temp;
	}
	else
		return temp;

	/* Tips:
	   - Allokera (t.ex. med malloc) tillrackligt med minne for att fa plats med str,
         glom inte att det maste finnas plats fšr \0 (nolltermineringen).
         Glom inte att testa sa att allokeringen lyckades
	   - Det Šr tillatet att anvŠnda inbyggda strangfunktioner (som t.ex strcpy())
	   - Kom ihag att anvanda assert() */

	// Postcondition: returvardet innehaller samma strang som 'str' - behšver inte testas med assert
}

int dstring_concatenate(DString* destination, DString source)
{
    // Precondition: destination Šr ej NULL
	// Precondition: *destination ar ej NULL
	// Precondition: source ar ej NULL
    // Preconditions testas med asserts.
	assert(destination != NULL);
	assert(*destination != NULL);
	assert(source != NULL);

	/* Tips: 
	   - Tank pŒ att *destination redan ar en dynamiskt allokerad strang
	   - Tank pŒ att vi kommer att behova allokera mer minne for att fa plats med den har langre strangen.
         Minnet som *destination pekar pa behover utokas (realloc), hur stort ska det "nya" minnet bli?
         Glom inte att nolltermineringen maste fa plats.
         Nar du allokerar minne dynamiskt maste du alltid testa sa att allokeringen lyckades innan du
         borjar jobba med minnet.
       - Det ar tillatet att anvanda inbyggda funktioner (som t.ex. strcat()).
    */

	int size = strlen(*destination) + strlen(source) + 1;	//+1 för att ha med '\0'
										    				//Ger nu totala längden som behövs i allokeringen

	DString temp = (DString)realloc(*destination, size * sizeof(char));
	if (temp != NULL) {
		strcat(temp, source);
		*destination = temp;
		return 1;
	}
	else
		return 0;

	// Postcondition: *destination innehaller den gamla strangen ihopslagen med source - behšver inte testas med assert.
}

void dstring_truncate(DString* destination, unsigned int truncatedLength)
{
	// Precondition: destination Šr ej NULL, *destination ar ej NULL
    // lŠngden (truncateLength) fŒr inte vara negativ
    // Preconditions testas med asserts
	assert(destination != NULL);
	assert(*destination != NULL);
	assert(truncatedLength >= 0);

	/* Tips:
	   - Anvand realloc for att frigora det overflodiga minnet
         (realloc frigor forst minnet och allokerar sedan nytt for den angivna storleken)
	   - glom inte nolltermineringen
     
     Vad hŠnder om truncateLength Šr lŠngre Šn vad strŠngen Šr?*/

	if (strlen(*destination) >= truncatedLength) {
		DString temp = (DString)realloc(*destination, (truncatedLength + 1) * sizeof(char));
		//Antar att truncatedLength ska vara antal chars utöver strängslut

		if (temp != NULL) {
			temp[truncatedLength] = '\0';
			*destination = temp;
		}
			
	}
	// Postcondition: *destination ar inte langre an 'truncatedLength' tecken - behšver inte testas med assert
}

void dstring_print(DString str, FILE* textfile)
{
	// Precondition: textfile ar inte NULL - maste testas innan du forsoker skriva till filen
    /*Tank pŒ att filpekaren kopplas till filen innan funktionen anropas*/
	assert(textfile != NULL);

	/* filpekaren far inte stangas, filen ska fungera som vanligt efter anropet */
    /*Den har funktionen ska vara generell, du ska kunna anvanda den for att skriva ut till
     en fil eller for att skriva ut i konsollen (pa skarmen). Om den anvands for att skriva till
     en extern fil sa kan du anta att filen oppnas och stangs innan respektive efter anrop till
     funktionen. Om den anvands for att skriva ut pa skarmen kan du anta att du far stdout till den
     andra parametern.

     Du ska inte skriva olika kod for att skriva till fil och till konsoll. Samma kod ska fungera for bada.*/

	fputs(str, textfile);
}

void dstring_delete(DString* stringToDelete)
{
	// Precondition: stringToDelete ar inte NULL
	assert(stringToDelete != NULL);

	free(*stringToDelete);
	*stringToDelete = NULL;

	// Postcondition: *stringToDelete ar NULL och minnet ar frigjort - behšver inte testas med assert
}
