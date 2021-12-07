#define _CRT_SECURE_NO_WARNINGS // Behovs i Visual studio for att tillata vissa funktioner
#include "HashTable.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "Person.h"
#define SIZE 10
#define LOOPS 1000

/*Typer fšr att hantera ett dynamiskt antal tabeller - anvands i compareHashTableSizes*/
typedef struct{
    HashTable table;
    int tableSize;
    int collissions;
}Table;

typedef struct{
    Table *Tables;
    int noOfTables;
}HTables;
/**********************************************/
static void fillArrayWithPersons(Person *list);
static int addPersonsToTable(HashTable *htable, Person *persons);
static int getTableSize(int nr);

/*Testfunktioner*/
void compareHashTableSizes(void);/*Valj hur manga olika hashtabellsstorlekar du vill jamfora. Lagger in samma data i samtliga storlekar och skriver ut antal krockar med respektive storlek*/
void test(void); /*Testar samtliga funktioner och olika fall fšr hashtabellen.*/
void menu(void); /*A menu to test your functions with manual data och random data*/


int main(void)
{
//    menu();
    test();
//    compareHashTableSizes();

	return 0;
}

/*********************************************************************************************************/
/*Funktioner fšr meny, testfunktion och for att jamfora krockar for olika storlekar pa hashtabellen*/
/*********************************************************************************************************/

static void fillArrayWithPersons(Person *list)
{
    for(int i = 0; i < SIZE; i++)
        list[i] = getRandomPerson();
}

static int addPersonsToTable(HashTable *htable, Person *persons)
{
    int collissions = 0;
    for(int i = 0; i < SIZE; i++)
    {
        collissions+=insertElement(htable, persons[i].personalNumber, persons[i]);
        assert(lookup(htable, persons[i].personalNumber)->personalNumber == persons[i].personalNumber);
    }
    return collissions;
}

static int getTableSize(int nr)
{
    int tableSize;

    do
    {
        printf("Size of hashtable %d (at least %d): ", nr, SIZE);
        scanf("%u", &tableSize); //det ar onskvart att lata storleken vara ett primtal
    } while (tableSize < SIZE);

    return tableSize;
}



/*Valj hur manga olika hashtabellsstorlekar du vill jamfora. Lagger in samma data i samtliga storlekar och skriver ut antal krockar med respektive storlek*/
void compareHashTableSizes(void)
{
    int noOfTables;
    HTables myTables;
    int i, j;
    
    printf("How many hashtables do you want to compare: ");
    scanf("%d", &noOfTables);
    if(noOfTables <= 0)
    {
        printf("No tables selected, shutting down\n");
        return;
    }
    
    myTables.Tables = (Table *)calloc(noOfTables, sizeof(Table));
    if(myTables.Tables == NULL)
    {
        printf("Error creating tables, shutting down\n");
        return;
    }
    
    for(j = 0; j < noOfTables; j++)
    {
        myTables.Tables[j].tableSize = getTableSize(j+1);
        assert(myTables.Tables[j].tableSize >= SIZE);
        myTables.Tables[j].collissions = 0;
    }
    
    Person listOfPersons[SIZE];
    
    for(i = 0; i < LOOPS; i++)
    {
        fillArrayWithPersons(listOfPersons); //fyller array
        
        for(j = 0; j < noOfTables; j++)
        {
            myTables.Tables[j].table = createHashTable(myTables.Tables[j].tableSize);
            myTables.Tables[j].collissions += addPersonsToTable(&(myTables.Tables[j].table), listOfPersons);
            freeHashTable(&(myTables.Tables[j].table));
        }
    }
    
    for(j = 0; j < noOfTables; j++)
        printf("Table %d (size %d) - number of collisions: %d\n", j+1, myTables.Tables[j].tableSize, myTables.Tables[j].collissions/LOOPS);
    
    
    free(myTables.Tables);
}




/*Testar samtliga funktioner och olika fall for hashtabellen. Du kan nar som helst lagga till ett anrop till printHashTable(&htable); for att se hur hashtabellen ser ut*/
void test(void)
{
    HashTable htable = createHashTable(10); /*En battre storlek for mŠngden 9 ar 13. Denna funktion (test) ar dock endast till for att testa att hashtabellens funktioner implementerats korrekt och %10 Šr lattare for gemene man att berakna Šn %13.*/
    assert(getSize(&htable) == 10);
    Person arrPersons[9] = {{931014, 81.0, "Tobias"},
                            {881011, 75.0, "Alva"},
                            {600704, 114.0, "Bengt"},
                            {790408, 93.5, "Nora"},
                            {900610, 71.3, "Aram"},
                            {510929, 83.6, "Jasmin"},
                            {740318, 63.0, "Emma"},
                            {801204, 93.4, "Ibrahim"},
                            {830709, 53.9, "Sara"}};
    Person aPerson;
    const Value *aPersonPointer;
    int i, collisions = 0;
    
    //lagg till nagra personer och kontrollera att de ligger pa ratt plats
    for(i = 0; i < 9; i++)
    {
        collisions+= insertElement(&htable, arrPersons[i].personalNumber, arrPersons[i]);
    }
    assert(htable.table[0].key == 900610);
    assert(htable.table[1].key == 881011);
    assert(htable.table[2].key == 740318);
    assert(htable.table[3].key == 830709);
    assert(htable.table[4].key == 931014);
    assert(htable.table[5].key == 600704);
    assert(htable.table[6].key == 801204);
    assert(htable.table[7].key == UNUSED);
    assert(htable.table[8].key == 790408);
    assert(htable.table[9].key == 510929);
    assert(collisions == 11);
    
    //lagg till dubblett av key - value ska uppdateras
    strcpy(aPerson.name, "Anna");
    aPerson.personalNumber = 881011;
    aPerson.weight = 65.2;
    insertElement(&htable, 881011,aPerson);
    assert(htable.table[1].value.weight == aPerson.weight);
    assert(strcmp(htable.table[1].value.name, aPerson.name) == 0);
    
    //Soker efter person som ligger pŒ ratt plats och person som ligger annan plats pga krock
    aPersonPointer = lookup(&htable, 790408);
    assert(strcmp(aPersonPointer->name, "Nora") == 0);
    aPersonPointer = lookup(&htable, 740318);
    assert(strcmp(aPersonPointer->name, "Emma") == 0);
    
    //Soker efter person som inte finns i tabellen
    assert(lookup(&htable, 600705) == NULL);
    

    //Ta bort en person som inte har nagra efterfoljande
    deleteElement(&htable, 801204);
    assert(lookup(&htable, 801204) == NULL);
    assert(htable.table[6].key == UNUSED);
    
    //Ta bort en person som har efterfoljande
    deleteElement(&htable, 790408);
    assert(lookup(&htable, 790408) == NULL);
    assert(htable.table[0].key == 900610);
    assert(htable.table[1].key == 881011);
    assert(htable.table[2].key == 830709);
    assert(htable.table[3].key == UNUSED);
    assert(htable.table[4].key == 931014);
    assert(htable.table[5].key == 600704);
    assert(htable.table[6].key == UNUSED);
    assert(htable.table[7].key == UNUSED);
    assert(htable.table[8].key == 740318);
    assert(htable.table[9].key == 510929);
    
    //Tom hela hashtabellen
    deleteElement(&htable, 900610);
    deleteElement(&htable, 881011);
    deleteElement(&htable, 830709);
    deleteElement(&htable, 931014);
    deleteElement(&htable, 600704);
    deleteElement(&htable, 740318);
    deleteElement(&htable, 510929);
    assert(htable.table[0].key == UNUSED);
    assert(htable.table[1].key == UNUSED);
    assert(htable.table[2].key == UNUSED);
    assert(htable.table[3].key == UNUSED);
    assert(htable.table[4].key == UNUSED);
    assert(htable.table[5].key == UNUSED);
    assert(htable.table[6].key == UNUSED);
    assert(htable.table[7].key == UNUSED);
    assert(htable.table[8].key == UNUSED);
    assert(htable.table[9].key == UNUSED);
    
    //Lagg till nagra
    insertElement(&htable, arrPersons[0].personalNumber, arrPersons[0]);
    assert(htable.table[4].key == 931014);
    insertElement(&htable, arrPersons[1].personalNumber, arrPersons[1]);
    assert(htable.table[1].key == 881011);
    insertElement(&htable, arrPersons[2].personalNumber, arrPersons[2]);
    assert(htable.table[5].key == 600704);
    insertElement(&htable, arrPersons[3].personalNumber, arrPersons[3]);
    assert(htable.table[8].key == 790408);
    
    //Tom och frigor tabellen
    freeHashTable(&htable);
    assert(htable.size == 0);
    assert(htable.table == NULL);
    
    
    printf("Your hashtable passed the test\n\n");
}

void menu(void)
{
    int choice, subChoice, size, pNr, collisions = 0;
    HashTable htable;
    Person aPerson;
    const Value *aPersonPointer;
    do{
        printf("\n----------Menu Hashtable----------\n1 - Create Hashtable\n2 - Insert element\n3 - Print hashtable\n4 - Search for element\n5 - Delete element\n6 - Get size of hashtable\n7 - Free hashtable\n8 - Exit\n");
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                size = getTableSize(0);
                htable = createHashTable(size);
                break;
            case 2:
                printf("1 - Random data\n2 - Manual data\n");
                scanf("%d", &subChoice);
                switch (subChoice) {
                    case 1:
                        aPerson = getRandomPerson();
                        printf("Random\n%d: %s: %f\n", aPerson.personalNumber, aPerson.name, aPerson.weight);
                        break;
                    case 2:
                        while(getchar()!='\n');
                        printf("Enter name: ");
                        fgets(aPerson.name, 28, stdin);
                        aPerson.name[strlen(aPerson.name)-1] = '\0'; /*ta bort enterslaget som fgets laser in i strangen*/
                        printf("Enter weight: ");
                        scanf("%f", &aPerson.weight);
                        printf("Enter personal number (YYMMDD): ");
                        scanf("%d", &aPerson.personalNumber);
                        break;
                    default: printf("Invalid input\n");
                        break;
                }
                
                if((collisions = insertElement(&htable, aPerson.personalNumber, aPerson)) >= 1)
                    printf("Insertion created %d collisions\n", collisions);
                break;
            case 3:
                printHashTable(&htable);
                break;
            case 4:
                printf("Enter personal number (YYMMDD) to search for: ");
                scanf("%d", &pNr);
                aPersonPointer = lookup(&htable, pNr);
                if(aPersonPointer == NULL)
                    printf("%d could not be found in the table\n", pNr);
                else
                    printf("Found\n%d: %s: %f\n", aPersonPointer->personalNumber, aPersonPointer->name, aPersonPointer->weight);
                break;
            case 5:
                printf("Enter personal number (YYMMDD) to delete: ");
                scanf("%d", &pNr);
                deleteElement(&htable, pNr);
                break;
            case 6:
                printf("Table size: %d\n\n", getSize(&htable));
                break;
            case 7:
                freeHashTable(&htable);
                break;
                
            default: printf("Invalid input\n");
                break;
        }
        
    }while(choice != 8);
}


