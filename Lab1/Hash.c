#include <stdio.h>

//This is a simple implementation of Hash Table by C
typedef HASHTABLE_INIT_SIZE 500;

typedef struct _bucket
{
	char *key;
	void *value;
	struct _bucket * next;
} Bucket;

typedef struct _HashTable
{
	int size;
	int elem_num;
	Bucket** buckets;
} HashTable;

static int hash_str(char *key)
{
	int hash = 0;
	char *cur = key;
	while(*cur != '\0')
	{
		hash += *cur;
		++cur;
	}
	return hash;
}

#define HASH_INDEX(ht, key) (hash_str((key)) % (ht)->size)

int hash_init(HashTable *ht); // initialize hash table
int hash_lookup(HashTable *ht, char *key, void **result); // look up certain content by key
int hash_insert(HashTable *ht, char *key, void *value); // insert key-value pair
int hash_remove(HashTable *ht, char *key); // remove a key-value pair
int hash_destory(HashTable *ht); // destory the whole hash table


int hash_init(HashTable *ht)
{
	ht->size =  HASHTABLE_INIT_SIZE;
	ht->elem_num = 0;
	ht->buckets = (Bucket **)malloc(ht->size, sizeof(Bucket *));
	if(!ht->buckets)	return FALSE;
	return TRUE;
}

int hash_insert(HashTable *ht, char *key, void *value)
{
	//check if we need to resize the hash table
	resize_hash_table_if_needed(ht);
	int index = HASH_INDEX(ht, key);
	Bucket *org_bucket = ht->buckets[index];
	Bucket *temp_bucket = org_bucket;

	//check if the key exits already
	while(temp_bucket)
	{
		if (strcmp(key, tmp_bucket->key)==0)
		{
			temp_bucket->value = value;
			return True;
		}
		temp_bucket = temp_bucket->next;

	}
	Bucket *bucket = (Bucket *)malloc(sizeof(Bucket));

	bucket->key = key;
	bucket->value = value;
	bucket->next = NULL;
	ht->elem_num += 1;

	if(org_bucket)
		bucket->next = org_bucket;


	ht->buckets[index] = bucket;
	return True;

}
