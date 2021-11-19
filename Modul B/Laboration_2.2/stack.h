/* Laboration 2 - Datastrukturer och Algoritmer */
/* Stack */

#ifndef STACK_H
#define STACK_H
#include "list.h"		// Din lista inkluderas


/*******************************************************************/
/* Stacken ska implementeras som en lankad lista.                  */
/* Du ska anvanda dina listfunktioner aven i stacken               */
/* Du ska alltsa varken skriva om funktionerna eller kopiera koden */
/* OBS! Du ska inte andra nagonting i interfacet                   */
/* Alla funktioner ska implementeras                               */
/*******************************************************************/
 
typedef List Stack;     // Ordet 'Stack' kommer att vara din listtyp


/* Skapar en ny tom stack */
Stack initializeStack(void);

/* Returnerar 1 om stacken ar tom, annars 0 */
int stackIsEmpty(const Stack stack);

/* Lagger ett element overst på stacken */
void push(Stack* pStack, const Data element);

/* Tar bort det oversta elementet fran stacken */
void pop(Stack* pStack);

/* Returnerar det oversta elementet pa stacken */
Data peekStack(const Stack stack);

/*Skriver ut hela stacken
 Endast till for testning och felsokning */
void printStack(const Stack stack, FILE *textfile);


#endif
