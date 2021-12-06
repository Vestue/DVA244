#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som är Hashtabellen */
static int hash(Key key, int tablesize)
{
	return -1;
}

/*Leta framåt enligt principen öppen adressering
 Antalet krockar returneras via pekaren col i parameterlistan*/
static int linearProbe(const HashTable* htable, Key key, unsigned int *col)
{
    return -1; // Ersatt med ett index
}

/*Allokera minne för hashtabellen*/
HashTable createHashTable(unsigned int size)
{
    // Dessa tva rader ar bara till for att labskelettet ska kompilera. Ta bort dessa nar du skriver funktionen.
    HashTable htable = { 0 };
    return htable;
}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
/* Returnerar antalet krockar (som räknas i linearProbe() )*/
unsigned int insertElement(HashTable* htable, const Key key, const Value value)
{
	// Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
    return 0; //Ersatt med ratt varde
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
    return NULL; // Ersatt med ratt varde
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
	// Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
    return 0; // Ersatt med ratt varde
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
