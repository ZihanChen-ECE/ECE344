#ifndef HASHMAP_H
#define HASHMAP_H

// hash map struct
struct s_hashmap;
typedef struct s_hashmap hashmap;

bool isPrime(int val);
int findPrimeGreaterThan(int val);

/** Creates a new hashmap near the given size. */
extern hashmap* hashmapCreate(int startsize);

/** Inserts a new element into the hashmap. */
void hashmapInsert(hashmap*, const void* data, unsigned long key);

/** Removes the storage for the element of the key and returns the element. */
void* hashmapRemove(hashmap*, unsigned long key);

/** Returns the element for the key. */
void* hashmapGet(hashmap*, unsigned long key);

/** Returns the number of saved elements. */
long hashmapCount(hashmap*);

/** Removes the hashmap structure. */
void hashmapDelete(hashmap*);

#endif