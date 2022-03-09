/*****************************************************
    Ragnar Winblad von Walter, rwr21002, 199702221798
    DVA244
    Laboration 4
*******************************************************/

#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

void emptyBucket(HashTable*, int);
void sortHashTable(HashTable*, int);

int changeSize(HashTable* htable, int newSize); // EXAMINATION, denna ligger l�ngst ned

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
/* Returnerar antalet krockar (som r�knas i linearProbe() )*/
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
    int col; // Anv�nds bara f�r att proba
    // Hitta index till nyckeln som ska tas bort
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
        else if (htable->table[index].key == UNUSED)   // Om platsen �r tom finns nyckeln ej i hashtabellen
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

        // Om slutet av hashTablet n�s eller om en nyckel har b�sta m�jliga index
        if (htable->table[currentIndex].key == 0)// || currentIndex == currentHash)   
            break;

        //  Om hashen matchar den tomma indexen  
        //  eller om avst�ndet fr�n startIndex till den index som hashen helst ska vara p�
        //  �r mindre �n dess avst�nd till index den ligger p� just nu.
        else if ((currentHash == startIndex) || i < abs(currentIndex - currentHash))
        {
            // Flyttar nyckeln till nya platsen
            htable->table[startIndex].key = htable->table[currentIndex].key;   
            htable->table[startIndex].value = htable->table[currentIndex].value;
            
            // Tar bort nyckeln och v�rdet fr�n gamla platsen
            emptyBucket(htable, currentIndex);

            // Kollar om en annan nyckel vill ha denna nya tomma plats
            sortHashTable(htable, currentIndex);  
            break;
        }
    }
    return;
}

// EXAMINATION
// Funktionen b�rjar med att kolla om den inmatade storleken �r st�rre �n den f�reg�ende storleken.
// Om det st�mmer kommer funktionen att f�rs�ka allokera en ny hashtabbel.
// Sedan ska den nya hashtabbellen fyllas med nycklar och v�rden f�r det gamla,
// den g�r detta genom att loopa igenom varje index och anv�nda nycklarna och v�rda p� det index f�r att g�ra en insert i nya tabellen.
// Detta g�r att nycklarna sorteras r�tt direkt n�r de s�tts in i nya hashtabellen.
// Sedan frig�rs den gamla tabellen och htable pekas om till den nya.

int changeSize(HashTable* htable, int newSize)
{
    // Det m�ste finnas en tabell att �ndra storlek p�
    assert(htable != NULL);

    int oldSize = getSize(htable);
    if (newSize < oldSize)
    {
        printf("\nNew size has to be bigger than the old one.\nOld size: %d", oldSize);
        return 1;
    }
    else
    {
        HashTable temp = createHashTable(newSize);
        if (temp.table == NULL)
            return 1;

        // Kopiera �ver all gammal data till r�tt plats i nya tabellen
        for (int i = 0; i < oldSize; i++)
        {
            (void)insertElement(&temp, htable->table[i].key, htable->table[i].value);
        }
        // Frig�r gamla tabellen och pekar om htable till nya
        freeHashTable(htable);
        htable->table = temp.table;
        htable->size = newSize;
    }

    assert(getSize(htable) == newSize);
    return 0;
}