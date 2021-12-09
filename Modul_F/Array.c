#include "Array.h"
#include "Statistics.h" 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int isSorted(const ElementType* array, size_t size)
{
	assert(array != NULL);

	unsigned int i;

	for (i = 1; i < size; i++)
		if (array[i] < array[i - 1])	// Om tva element ar i fel ordning ar elementen ej sorterade
			return 0;
	return 1;
}

ElementType* createForwardSortedArray(size_t size)
{
	ElementType* array = malloc(sizeof(ElementType)*size);
	unsigned int i;

	if (array != NULL)
	{
		for (i = 0; i < size; i++)
			array[i] = i;

		assert(isSorted(array, size));
	}
	return array;
}

ElementType* createBackwardSortedArray(size_t size)
{
	ElementType* array = malloc(sizeof(ElementType)*size);
	unsigned int i;

	if (array != NULL)
	{
		for (i = 0; i < size; i++)
			array[i] = size - i;

		assert(!isSorted(array, size));
	}
	return array;
}

ElementType* createUnsortedArray(size_t size)
{
	srand(SEED); // Se till att varje osorterad array ar lika

	ElementType* array = createForwardSortedArray(size); // Borja med en sorterad array
	unsigned int randomIndex1, randomIndex2;
	unsigned int i;

	if (array != NULL)
	{
		// Byt plats pa element slumpmassigt
		for (i = 0; i < size; i++)
		{
			// Valj tva slumpmassiga index och byt plats pa dem
			randomIndex1 = rand() % size;
			randomIndex2 = rand() % size;
			swapElements(&array[randomIndex1], &array[randomIndex2], NULL);
		}
	}
	return array;
}

void printArray(const ElementType* array, size_t size, FILE* file)
{
	assert(array != NULL);

	unsigned int i;
	printf("[");
	for (i = 0; i < size; i++)
		fprintf(file, "%u ", array[i]);
	printf("]\n");
}
