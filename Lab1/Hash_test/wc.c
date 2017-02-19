#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "wc.h"
#include <string.h>
#include <math.h>
#include <ctype.h>

//#include "stringList.h"//I should have really implemented the linked list in another file but I hate linking

//this is the hash table struct
struct wc {
    struct stringList** buckets;//array of linked list head pointers
    int tablesize;//size of the table
    
};

//LINKED LIST IMPLEMENTATION BEGINS HERE

struct stringList{
    struct stringList* next;  
    char* keystr;
    int count;
};

void sl_destroy(struct stringList *sl)
{
    
    struct stringList *handle;
    struct stringList* target;
    handle = sl->next;
    target = NULL;
    while(handle != NULL){
        target = handle;
        handle = handle->next;
        free(target->keystr);
        free(target);
    }
    free(sl);
}

//attempts to add an entry to the hash table. If it already exists in the table, increments its value
int sp_add_edit(struct stringList *sl, char* key)
{
    if(sl == NULL){
        return 0;
    }
    struct stringList* handle;
    struct stringList* newpt;
    handle = sl;
    //just insert the puppy at the end of the list. If the puppy exists, increment it and return
    while(handle != NULL){
        if(!strcmp(handle->keystr,key)){//if the element is found in the list already, increment the value to keep a word count
            handle->count ++;
            return 0;
        }
        sl = handle;
        handle=handle->next;
    }
    newpt = (struct stringList*)malloc(sizeof(struct stringList));
    assert(newpt);
    newpt->count = 1;
    newpt->keystr = key;
    newpt->next = NULL;
    sl->next = newpt;
    return 1;
}

//find an element in a linked list with a matching key and return a pointer to it
struct stringList* sp_find_element(struct stringList* sl,char* key){
    struct stringList* handle = sl;
    while(handle->next != NULL){
        if(strcmp(key,handle->keystr)){
            return handle;      
        }
    }
    return NULL;
}



//LINKED LIST IMPLEMENTATION ENDS HERE



//this is the linked list struct

//this is the djb2 hash function by Dan Bernstein
int hashfunc(char* str){
    unsigned long hash = 5381;
    int c;
    while((c=*str++)){
        hash=((hash << 5) + hash)+c; 
    }
    return abs(hash); 
}

//string 

struct wc *wc_init(char *word_array, long size)
{   
    int i,j,arraylen,wcount=0,charcount =0,findex=0,hashval=0;
    char*tempstr=NULL;//pointers to first and last words in the string array, temp string to be inserted to table
    struct wc *wc;
    tempstr=NULL;
    wc = (struct wc *)malloc(sizeof(struct wc));
    assert(wc);
    arraylen = strlen(word_array);
    wcount = round(strlen(word_array)/(4.79*0.75));//this will be the number of buckets, there are an average of 4.79 characters per word and I wish to use a load factor of 0.75. '
    (*wc).buckets = (struct stringList**)malloc(sizeof(struct stringList*)*wcount);
    wc->tablesize = wcount;
    //initialize the head node for each bucket in the table
    for(i=0;i<wcount;i++){
        wc->buckets[i] = (struct stringList *)malloc(sizeof(struct stringList)); //pretty much sl_init function for the linked list
        wc->buckets[i]->next = NULL;
        wc->buckets[i]->count = -1;
        wc->buckets[i]->keystr = "";
    }
    //loop through each character in the string, and add it to the hash table
    for(i=0;i<arraylen;i++){
        charcount ++;
        if(isspace(word_array[i])){
            if(charcount < 2){//if the character in question is just 1 white space, we need to skip it but still increment the pointers
                findex += charcount;
                charcount = 0;
                continue;
            }
            tempstr = malloc(sizeof(char)*(charcount));
            for(j=0;j<charcount;j++){//copies a word into a temporary string
                tempstr[j] = *(word_array+findex+j);
            }
                    tempstr[charcount-1] = 0;
            findex+=charcount;
            
            //push tempstr into the hash table here
            
            hashval = hashfunc((tempstr))%wcount;

            if(!sp_add_edit(wc->buckets[hashval],(tempstr))){//inserts/increments, depending on what hapepns there may be a need to free tempstr    
                free(tempstr);
            }
            charcount = 0;
                
        }
    }
        return wc;
}

void
wc_output(struct wc *wc)
{
    unsigned int i=0;
    struct stringList* handle=NULL;
    for(;i<wc->tablesize;i++){
        handle=wc->buckets[i];
        if(handle->next == NULL){
            continue;
        }
                handle = handle->next;
        for(;handle!=NULL;handle=handle->next){
            fprintf(stdout,"%s:%d\n",handle->keystr,handle->count);
        }
    }
}

void
wc_destroy(struct wc *wc)
{
    unsigned int i=0;
    for(;i<wc->tablesize;i++){
        sl_destroy(wc->buckets[i]);
    }
    free(wc->buckets);
    free(wc);
}