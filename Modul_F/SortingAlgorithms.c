#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
      case BUBBLE_SORT:
      case INSERTION_SORT:
//      case SELECTION_SORT:
//      case QUICK_SORT:
      case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}

/*Antalet byten i en och samma algoritm kan vara olika beroende p� implementationen. Ibland ligger datat redan p� r�tt plats och d� kan man v�lja att testa det och inte g�ra ett byte (vilket ger extra j�mf�relse) eller s� kan man �nd� g�ra ett byte (med sig sj�lv). F�ljer man de algoritmer som vi g�tt igenom p� f�rel�sningarna exakt s� g�r man en swap �ven p� ett element som ligger p� r�tt plats
 
    N�r du analyserar det data som genereras (result.txt) s� beh�ver du ha detta i �tanke */

/******************************************************************************************/
/* Era algoritmer har: */

static void bubbleSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	printArray(arrayToSort, size, stdout);
	int changeMade;
	do
	{
		changeMade = 0;	// Anv�nds f�r att avg�ra om sorteringen �r f�rdig.
		for (int i = 0; lessThan(i, size - 1, statistics); i++)
		{
			if (greaterThan(arrayToSort[i], arrayToSort[i + 1], statistics))
			{
				swapElements(&arrayToSort[i], &arrayToSort[i + 1], statistics);
				changeMade = 1;
			}
		}
	} while (changeMade != 0);
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	for (int i = 0, elementsInLeft = 1; lessThan(i, size - 1, statistics); i++, elementsInLeft++)
	{
		// Om h�gra talet �r st�rre flyttas v�nsterdelen bara fram ett steg.
		// Om talet �r mindre m�ste de j�mf�ras med elementen i v�nsterarrayen f�r att f� r�tt plats.
		if (lessThan(arrayToSort[i + 1], arrayToSort[i], statistics))
		{
			for (int j = 0; lessThan(j, elementsInLeft, statistics); j++)
			{
				if (lessThan(arrayToSort[i + 1], arrayToSort[j], statistics))
				{
					swapElements(&arrayToSort[i + 1], &arrayToSort[j], statistics);
				}
			}
		}
	}
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static int* allocateArray(int size)
{
	int* temp = (int*)malloc(sizeof(int) * size);
	return temp;
}

static void mergeBack(ElementType* arrayToSort, unsigned int first, unsigned int mid, unsigned int last, Statistics* statistics)
{
	int leftSize = mid - first + 1, rightSize = last - mid;
	int* leftArray = allocateArray(leftSize);
	int* rightArray = allocateArray(rightSize);
	if (leftArray == NULL || rightArray == NULL)	// isEqual hanterar inte pekare
	{
		printf("\nAbort!");
		return;
	}

	for (int i = 0; lessThan(i, leftSize, statistics); i++)
		leftArray[i] = arrayToSort[i + first];
	for (int i = 0; lessThan(i, rightSize, statistics); i++)
		rightArray[i] = arrayToSort[mid + i + 1];
	
	// Flyttar �ver minsta element fram tills slutet p� n�n av arrayerna
	int l = 0, r = 0, i = first;
	for (; lessThan(l, leftSize, statistics) && lessThan(r, rightSize, statistics); i++)
	{
		if (lessThanOrEqualTo(leftArray[l], rightArray[r], statistics))
		{
			arrayToSort[i] = leftArray[l];
			l++;
		}
		else
		{
			arrayToSort[i] = rightArray[r];
			r++;
		}
	}
	// Flyttar �ver det som �r kvar
	for (; lessThan(l, leftSize, statistics); i++, l++)
		arrayToSort[i] = leftArray[l];
	for (; lessThan(r, rightSize, statistics); i++, r++)
		arrayToSort[i] = rightArray[r];

	free(leftArray);
	free(rightArray);
}

static void mergeHelp(ElementType* arrayToSort, unsigned int first, unsigned int last, Statistics* statistics)
{
	if (equalTo(first, last, statistics))
		return;
	unsigned int mid = (first + last) / 2;
	mergeHelp(arrayToSort, first, mid, statistics); // Sortera v�nster
	mergeHelp(arrayToSort, mid + 1, last, statistics); // Sortera h�ger
	mergeBack(arrayToSort, first, mid, last, statistics);
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	mergeHelp(arrayToSort, 0, size - 1, statistics);
	/*
	// N�r arrayen har delats s� m�nga g�nger att det bara finns ett element kommer det f�rsta elementet vara samma som sista
	if (equalTo(arrayToSort[0], arrayToSort[size - 1], statistics))
		return;
	unsigned int mid = size / 2;
	printArray(arrayToSort, size, stdout);
	mergeSort(arrayToSort, mid, statistics); // Sortera v�nster
	mergeSort(&arrayToSort[mid + 1], size, statistics); // Sortera h�ger
	mergeHelp(arrayToSort, mid, size - 1, statistics);
	printArray(arrayToSort, size, stdout);*/
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet �r: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
