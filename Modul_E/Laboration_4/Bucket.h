#ifndef BUCKET_H
#define BUCKET_H
#include "Person.h"

typedef Person Value;
typedef int Key;

struct Bucket
{
	Key key;
	Value value;
};

#endif
