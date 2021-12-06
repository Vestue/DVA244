#define _CRT_SECURE_NO_WARNINGS // Behovs i Visual studio for att tillata vissa funktioner
#include "Person.h"
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

static void getRandomName(char* name)
{
	assert(name != NULL);

	char* names[] = { "Stefan", "Anna" , "Aram", "Sture", "Johan", "Jasmin", "Alva", "Nora", "Emma", "Linnea", "Lena", "Johanna",
		"Moa", "Per", "Alex", "Fredrik", "Kent", "Ibrahim", "Malin", "Sara", "Ida", "Hanna", "Sixten", "Birger" };

	const int numberOfNames = sizeof(names) / sizeof(char*);
	int index = rand() % numberOfNames;
	strcpy(name, names[index]);
}

static int getRandomPersonalNumber(void)
{
	int day = rand() % 30 + 1; // For enkelhetens skull antar vi att vaje manad har 30 dagar (blir vissa omojliga datum i februari, men det ar inte viktigt har)
	int month = rand() % 12 + 1;
	int year = rand() % 60 + 40;
	return day + 100 * month + 10000 * year;
}

Person getRandomPerson(void)
{
	Person randomPerson;
	getRandomName(randomPerson.name);
	randomPerson.personalNumber = getRandomPersonalNumber();
	randomPerson.weight = (float)(rand() % 70 + 50);
	return randomPerson;
}

void printPerson(Person* personToPrint, int index)
{
    printf("%d --- %d: %s, weight: %f ", index, personToPrint->personalNumber, personToPrint->name, personToPrint->weight);
}
