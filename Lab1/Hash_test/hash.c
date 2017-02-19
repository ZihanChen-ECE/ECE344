#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "wc.h"
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct hash_node{
	int cnt;
	char* key;
	struct hash_node* next;
}HashNode;

struct wc{
	HashNode *HashTable;
	int tableSize;
}




