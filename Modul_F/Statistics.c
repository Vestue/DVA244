#include "Statistics.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void resetStatistics(Statistics* statistics)
{
	assert(statistics != NULL);

	statistics->comparisons = 0;
	statistics->swaps = 0;
}

void printStatistics(const Statistics* statistics, FILE* file)
{
	assert(statistics != NULL);
	assert(file != NULL);

	fprintf(file, "%5u jämförelser, %5u byten", statistics->comparisons, statistics->swaps);
}


int lessThan(int element1, int element2, Statistics* statistics)
{
	assert(statistics != NULL);
	statistics->comparisons++;
	return element1 < element2;
}

int greaterThan(int element1, int element2, Statistics* statistics)
{
	assert(statistics != NULL);
	statistics->comparisons++;
	return element1 > element2;
}

int equalTo(int element1, int element2, Statistics* statistics)
{
	assert(statistics != NULL);
	statistics->comparisons++;
	return element1 == element2;
}

int notEqualTo(int element1, int element2, Statistics* statistics)
{
    assert(statistics != NULL);
    statistics->comparisons++;
    return element1 != element2;
}

int lessThanOrEqualTo(int element1, int element2, Statistics* statistics)
{
	assert(statistics != NULL);
	statistics->comparisons++;
	return element1 <= element2;
}

int greaterThanOrEqualTo(int element1, int element2, Statistics* statistics)
{
	assert(statistics != NULL);
	statistics->comparisons++;
	return element1 >= element2;
}


void swapElements(int* element1, int* element2, Statistics* statistics)
{
	assert(element1 != NULL && element2 != NULL);

	int temp = *element1;
	*element1 = *element2;
	*element2 = temp;

	if (statistics)
		statistics->swaps++;
}
