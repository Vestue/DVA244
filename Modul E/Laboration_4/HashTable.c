#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void nullifyPerson(HashTable*, int);
void sortHashTable(HashTable*, int);

	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som �r Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key%tablesize;
}

/*Leta fram�t enligt principen �ppen adressering
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
        return -1;  // Anv�nder negativa tal som ERR d� index ej kan vara negativt.
    }
    else
        return hash;
}

/*Allokera minne f�r hashtabellen*/
HashTable createHashTable(unsigned int size)
{
    HashTable htable = { 0 };
    struct Bucket* temp = (struct Bucket*)malloc(size * sizeof(struct Bucket));
    if (temp != NULL)
    {
        htable.table = temp;    //OBS! Kan beh�va initiera delarna i bucketen
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
/* Returnerar antalet krockar (som r�knas i linearProbe() )*/
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
    int col; // Anv�nds bara f�r att proba
    int toDeleteIndex = linearProbe(htable, key, &col);

    if (toDeleteIndex == -1 || htable->table[toDeleteIndex].key == NULL)
    {
        printf("\nCan't find key.");
        return;
    }
    // Tar bort datan och nyckeln.
    htable->table[toDeleteIndex].key = NULL;
    nullifyPerson(htable, toDeleteIndex);

    // Sortera listan

	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
    assert(lookup(htable, key) == NULL);
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
        else if (htable->table[index].key == NULL)   // Om platsen �r tom finns nyckeln ej i hashtabellen
            break;                                  // Detta f�ruts�tter att sorteringen skett r�tt om n�got har tagits bort p� platsen och nyckeln finns i listan
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

void nullifyPerson(HashTable* htable, int index)
{
    *htable->table[index].value.name = NULL;
    htable->table[index].value.personalNumber = 0;
    htable->table[index].value.weight = 0.0;
}

void sortHashTable(HashTable* htable, int startIndex)
{
    int prevIndex = (startIndex + 1) % htable->size, nextIndex;
    for (int i = 0; i < htable->size; i++)
    {
        nextIndex = (prevIndex + i) % htable->size;

        // Om slutet av hashTablet n�s eller om en nyckel har b�sta m�jliga index
        if (htable->table[nextIndex].key == NULL || nextIndex == hash(htable->table[nextIndex].key, htable->size))   
            break;
         
        else if ((htable->table[nextIndex].key % htable->size) == startIndex)   // DET H�R �R KNAPPT L�SBART
        {
            htable->table[startIndex].key = htable->table[nextIndex].key;   // Flyttar nyckeln till nya platsen
            htable->table[startIndex].value = htable->table[nextIndex].value;
            
            htable->table[nextIndex].key = NULL; // Tar bort nyckeln och v�rdet fr�n gamla platsen
            nullifyPerson(htable, nextIndex);

            sortHashTable(htable, nextIndex);   // Kollar om en annan nyckel vill ha denna nya tomma plats
            break;
        }
    }
    return;
}