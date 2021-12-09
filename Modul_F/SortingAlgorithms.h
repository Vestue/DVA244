#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include<stdlib.h>
#include<stdio.h>
#include "Statistics.h"

#define NUMBER_OF_SIZES 3 // Hur manga storlekar vi vill sortera

typedef enum { BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, MERGE_SORT, QUICK_SORT, SORTING_ALGORITHMS } SortingAlgorithm;
typedef unsigned int ElementType;

// Innehaller all information som behovs for att kunna sortera en array och ge statistik
typedef struct
{
	SortingAlgorithm algorithm;
	ElementType* arrayToSort;
	unsigned int arraySize;
	Statistics statistics;
} SortingArray;

// Returnerar namnet pa en algoritm
char* getAlgorithmName(SortingAlgorithm algorithm);

// Sorterar och skriver ut statistik for en array av arrayer
void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file);

// Returnerar 1 ifall den angivna algoritmen Šr implementerad, 0 annars
int isImplemented(SortingAlgorithm algorithm);

// Frigor minne for en en array av arrayer
void freeArray(SortingArray array[]);
#endif

