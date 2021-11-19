/* Laboration 2 - Datastrukturer och Algoritmer */
/* Set */

#ifndef SET_H
#define SET_H
#include "list.h"   // Din lista inkluderas 

/*******************************************************************/
/* Settet ska implementeras som en lankad lista.                   */
/* Du ska anvanda dina listfunktioner aven i ditt set              */
/* Du ska alltsa varken skriva om funktionerna eller kopiera koden */
/* OBS! Du ska inte andra nagonting i interfacet                   */
/* Alla funktioner ska implementeras                               */
/*******************************************************************/

typedef List Set;    // Ordet 'Set' kommer att vara din listtyp

/* Skapar et ny tomt set */
Set initializeSet(void);

/*Lagger till element i set
  Tank på att alla element i settet ska vara unika */
void addToSet(Set* set, const Data element);

/*Ta bort det angivna elementet från settet*/
void removeFromSet(Set* set, const Data element);

/*Returnerar 1 om elementet finns i set, annars 0 */
int isInSet(const Set set, const Data element);

/*Skriver ut hela settet
 Endast till for testning och felsokning */
void printSet(const Set set, FILE *textfile);


#endif
