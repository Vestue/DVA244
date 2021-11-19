/* Laboration 2 - Datastrukturer och Algoritmer */
/* Lankad lista */

#ifndef LIST_H
#define LIST_H
#include <stdio.h>


/**********************************************************************/
/*                                                                    */
/* Bestam om du vill gora en enkellankad eller en dubbellankad lista, */
/* valj motsvarande struct-definiton nedan.                           */
/* Oberoende av ditt val sa ser funktionsdeklarationerna likadana ut. */
/*                                                                    */
/* OBS!                                                               */
/* Du ska inte andra nagonting i interfacet                           */
/* Alla funktioner ska implementeras (i list.c)                       */
/**********************************************************************/


typedef int Data;


/*Valj denna struktdefinition om du vill implementera en dubbellankad lista*/
struct node
{
    Data data;
    struct node *next;
    struct node *previous;
};

/*Valj denna struktdefinition om du vill implementera en enkellankad lista*/
/*struct node
{
    Data data;
    struct node *next;
};*/

//Listan representeras av en nodpekare
typedef struct node *List;

//Returnera en tom lista
List createEmptyList(void);


//Ar listan tom?
//Returnerar 1 om listan ar tom, annars 0
int isEmpty(const List list);

//Lagg till nod forst i listan
void addFirst(List *list, const Data data);

//lagg till nod sist i listan
void addLast(List *list, const Data data);

//Ta bort forsta noden i listan
void removeFirst(List *list);

//ta bort sista noden i listan
void removeLast(List *list);

//ta bort data ur listan (forsta forekomsten), returnera 0 om datat inte finns, annars 1
int removeElement(List *list, const Data data);

//Sok efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data);

//returnera hur manga noder som finns i listan
int numberOfNodesInList(const List list);

//tom listan /ta bort allt data (alla noder) ur listan
void clearList(List *list);

//Skriv ut listan
void printList(const List list, FILE *textfile);

//returnera forsta datat i listan
Data getFirstElement(const List list);

//returnera sista datat i listan
Data getLastElement(const List list);


#endif
