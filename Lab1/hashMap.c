#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* this should be prime */
#define TABLE_STARTSIZE 1000

#define ACTIVE 1


typedef struct {
	void* data;
	int flags;
	long key;	
} hashEntry;

struct s_hashmap{
	hashEntry* table;
	long size, count;
};

bool isPrime(int val)
{
	// sqrt() takes double floating as argument
	int k = (int)sqrt((double)val);	
  	for (int i = 2; i <= k; i++)
  	{
  		if (m%i == 0)
  			break;
  	}
  	if (i > k)
  		return true;
  	else
  		return false;
  	
}

int findPrimeGreaterThan(int val)
{
  if (val & 1)
    val+=2;
  else
    val++;
  
  while (!isPrime(val))
    val+=2;
  
  return val;
}

void rehash(hashmap* hm)
{
	long size = hm->size;
	hm->size = findPrimeGreaterThan(size<<1);
}


