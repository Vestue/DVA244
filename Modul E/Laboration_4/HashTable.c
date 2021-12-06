#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som Šr Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key%tablesize;
}

/*Leta framŒt enligt principen šppen adressering
 Antalet krockar returneras via pekaren col i parameterlistan*/
static int linearProbe(const HashTable* htable, Key key, unsigned int *col)
{
    int i = 0;
    *col = 1;
    int hash = (key + i) % htable->size;

    while (*col != htable->size)
    {
        if (htable->table[hash].key == key || htable->table[hash].key == NULL)
            break;
        i++;
        (*col)++;
        hash = (key + i) % htable->size;
    }
    if (*col == htable->size)
    {
        //printf("\nTable is full. ");
        return -1;  // Använder negativa tal som ERR då index ej kan vara negativt.
    }
    else
        return hash;
}

/*Allokera minne fšr hashtabellen*/
HashTable createHashTable(unsigned int size)
{
    HashTable htable = { 0 };
    struct Bucket* temp = (struct Bucket*)malloc(size * sizeof(struct Bucket));
    if (temp != NULL)
    {
        htable.table = temp;    //OBS! Kan behöva initiera delarna i bucketen
        htable.size = size;
        return htable;
    }
    else
    {
        printf("\nFailed to allocate.");
        return htable;
    }
}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
/* Returnerar antalet krockar (som rŠknas i linearProbe() )*/
unsigned int insertElement(HashTable* htable, const Key key, const Value value)
{
    unsigned int col = 0;
    int index = hash(key, htable->size);
    if (htable->table[index].key != NULL || htable->table[index].key != key)
    {
        index = linearProbe(htable, key, &col);

        if (index == -1) // Utifall listan var full
        {
            printf("\nList is full.");
            return col;
        }
    }
    htable->table[index].key = key;
    htable->table[index].value = value;
	
    assert(lookup(htable, key) != NULL);    // Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
    return col;
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
    int col; // Används bara för att proba
    int toDeleteIndex = linearProbe(htable, key, &col);

    if (toDeleteIndex == -1)
    {
        printf("\nCan't find key.");
        return;
    }
	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
    int index;
    for (int i = 0; i < htable->size; i++)
    {
        index = (key + i) % htable->size;
        if (htable->table[index].key == key)
            return &htable->table[index].value;
        else if (htable->table[index].key == NULL)   // Om platsen är tom finns nyckeln ej i hashtabellen
            break;
    }
    return NULL; // Om i blir lika stor som htable->size har den loopat igenom hela arrayen.
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
    free(htable->table);
    htable->table = NULL;
    htable->size = 0;
    assert(getSize(htable) == 0);   // Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
    return htable->size;
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
