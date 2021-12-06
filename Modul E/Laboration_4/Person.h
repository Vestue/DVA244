#ifndef PERSON_H
#define PERSON_H

typedef struct
{
	int personalNumber;
	float weight;
	char name[28];
} Person;

Person getRandomPerson(void);
void printPerson(Person* personToPrint, int index);

#endif
