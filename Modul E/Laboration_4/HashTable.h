#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Bucket.h"
#define UNUSED 0

/*Hashtabell som loser krockar med hjalp av oppen adressering*/
typedef struct 
{
	struct Bucket* table; //Hashtabellen är en array av Buckets
	unsigned int size; // Storleken på Hashtabellen
} HashTable;

/*Allokerar minne för tabellen*/
HashTable createHashTable(unsigned int size);

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet modifieras */
/* Returnerar antalet krockar*/
unsigned int insertElement(HashTable* htable, const Key key, const Value value);

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key);

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key);

/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable);

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable);

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable); 

#endif
