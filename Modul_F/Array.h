#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <stdio.h>

/********************************************************

DVA104, Lab 5, Array.h
Innehaller funktioner for att hantera dynamiska arrayer.

*********************************************************/

#define SEED 245802 // Detta gor att vi far samma osorterade array varje gang, for att vi latt ska kunna jamfora. Man kan andra pa denna till vad som helst om man vill
typedef unsigned int ElementType;

// Avgor om "array" ar sorterad eller ej
int isSorted(const ElementType* array, size_t size);

// Skapar arrayer av given storlek och sortering
// Notera att dessa arrayer ar dynamiskt allokerade och att minnet behover frigoras nar man anvant dem fardigt
ElementType* createForwardSortedArray(size_t size);
ElementType* createBackwardSortedArray(size_t size);
ElementType* createUnsortedArray(size_t size);

// Skriver en array till fil
void printArray(const ElementType* array, size_t size, FILE* file);



#endif
