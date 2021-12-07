#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void emptyBucket(HashTable*, int);
void sortHashTable(HashTable*, int);

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
    int hash = (key + i) % htable->size;

    while (*col != htable->size)
    {
        if (htable->table[hash].key == key || htable->table[hash].key == UNUSED)
            break;
        i++;
        (*col)++;
        hash = (key + i) % htable->size;
    }
    if (*col == htable->size)
    {
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
        htable.table = temp;    
        htable.size = size;
        for (unsigned int i = 0; i < size; i++)  // Initierar alla hinkar
            emptyBucket(&htable, i);  
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
    if (htable->table[index].key != UNUSED || htable->table[index].key != key)
    {
        index = linearProbe(htable, key, &col);

        if (index == -1)
        {
            printf("\nList is full.");
            return col;
        }
    }
    htable->table[index].key = key;
    htable->table[index].value = value;
	
    // Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
    assert(lookup(htable, key) != NULL);    

    //printf("\n%d\n", col); // TEST
    return col;
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
    int col; // Används bara för att proba
    int toDeleteIndex = linearProbe(htable, key, &col);

    if (toDeleteIndex == -1 || htable->table[toDeleteIndex].key == UNUSED)
    {
        printf("\nCan't find key.");
        return;
    }
    // Tar bort datan och nyckeln.
    emptyBucket(htable, toDeleteIndex);

    // Sortera listan
    sortHashTable(htable, toDeleteIndex);

	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
    assert(lookup(htable, key) == NULL);
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
    int index;
    for (unsigned int i = 0; i < htable->size; i++)
    {
        index = (key + i) % htable->size;
        if (htable->table[index].key == key)
            return &htable->table[index].value;
        else if (htable->table[index].key == UNUSED)   // Om platsen är tom finns nyckeln ej i hashtabellen
            break;                                  // Detta förutsätter att sorteringen skett rätt om något har tagits bort på platsen och nyckeln finns i listan
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
    for (unsigned int i = 0; i < htable->size; i++)
    {
        printf("\n%d : %d", i, htable->table[i].key);
    }
}

void emptyBucket(HashTable* htable, int index)
{
    htable->table[index].key = UNUSED;
    *htable->table[index].value.name = '\0';
    htable->table[index].value.personalNumber = 0;
    htable->table[index].value.weight = 0.0;
}

void sortHashTable(HashTable* htable, int startIndex)
{
    int prevIndex = (startIndex + 1) % htable->size, currentIndex, currentHash;
    for (int i = 0; i < htable->size; i++)
    {
        currentIndex = (prevIndex + i) % htable->size;
        currentHash = hash(htable->table[currentIndex].key, htable->size);

        // Om slutet av hashTablet nås eller om en nyckel har bästa möjliga index
        if (htable->table[currentIndex].key == 0)// || currentIndex == currentHash)   
            break;

        //  Om hashen matchar den tomma indexen  
        //  eller om avståndet från startIndex till den index som hashen helst ska vara på
        //  är mindre än dess avstånd till index den ligger på just nu.
        else if ((currentHash == startIndex) || i < abs(currentIndex - currentHash))
        {
            // Flyttar nyckeln till nya platsen
            htable->table[startIndex].key = htable->table[currentIndex].key;   
            htable->table[startIndex].value = htable->table[currentIndex].value;
            
            // Tar bort nyckeln och värdet från gamla platsen
            emptyBucket(htable, currentIndex);

            // Kollar om en annan nyckel vill ha denna nya tomma plats
            sortHashTable(htable, currentIndex);  
            break;
        }
    }
    return;
}