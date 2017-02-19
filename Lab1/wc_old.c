#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "wc.h"

unsigned int hushval=0;
struct wordss{
char t[500];
int num;
};

struct wc {
struct wordss ** words;
int size;

	/* you can define this struct to have whatever fields you want. */
};



struct wc *
wc_init(char *word_array, long size) {
    struct wc *wc;
    if (size < 1)
        return NULL;
    wc = (struct wc *) malloc(sizeof (struct wc));
    wc->words = malloc(sizeof (struct wordss*)*size);
    int i = 0;
    while (i < size) {
        wc->words[i] = NULL;
        i++;
    }
    wc->size = size;

    assert(wc);

    i = 0;
    char oneWord[500];
    int wordi = 0;
    while (i < size) {
        int flag = isspace(word_array[i]);
        if (flag == 0) {
            oneWord[wordi] = word_array[i];
            wordi++;
            hushval = word_array[i]+(hushval << 5) - hushval;
            hushval = hushval % size;

        } else {
            oneWord[wordi] = '\0';
            wordi = 0;
            if (wc->words[hushval] == NULL) {
                wc->words[hushval] = (struct wordss *) malloc(sizeof (struct wordss));
                // wc->words[hushval]->t=strdup(&oneWord[0]);
                int k = 0;
                while (oneWord[k] != '\0') {
                    wc->words[hushval]->t[k] = oneWord[k];
                    k++;
                }
                wc->words[hushval]->t[k] = '\0';
                // char *str=wc->words[hushval]->t;
                // strcpy(wc->words[hushval]->t,oneWord);
                wc->words[hushval]->num++;
            } else {
                int judge = strcmp(wc->words[hushval]->t, oneWord);

                //                    if(judge==0){
                //                        wc->words[hushval]->num++;
                //                    }
                while (judge != 0 && wc->words[hushval] != NULL) {

                    hushval++;
                    hushval = hushval % size;
                    if (wc->words[hushval] != NULL)
                        judge = strcmp(wc->words[hushval]->t, oneWord);
                }
                if (judge == 0) {
                    wc->words[hushval]->num++;
                } else {
                    wc->words[hushval] = (struct wordss *) malloc(sizeof (struct wordss));
                    int k = 0;
                    while (oneWord[k] != '\0') {
                        wc->words[hushval]->t[k] = oneWord[k];
                        k++;
                    }
                    wc->words[hushval]->t[k] = '\0';
                    // wc->words[hushval]->t=strdup(&oneWord[0]);
                    //  strcpy(wc->words[hushval]->t,oneWord);
                    wc->words[hushval]->num++;
                }
            }
            hushval = 0;
        }
        i++;
    }
    //TBD();

    return wc;
}


void
wc_output(struct wc *wc) {
   // char *str = wc->words[11]->t;
    int i = 0;
    while (i < wc->size) {
        if (wc->words[i] != NULL) {
            if(wc->words[i]->t[0] !='\0'){
            printf("%s", wc->words[i]->t);
            printf(":%d\n", wc->words[i]->num);}
        
        }
        i++;
    }
    //printf("%s", str);

    //TBD();
}

void
wc_destroy(struct wc *wc) {
    //TBD();
    if(wc==NULL)
        return;
    int i=0;
    while(i<wc->size){
        if(wc->words[i]!=NULL){
            free(wc->words[i]);
        }
        i++;
    }
    free(wc->words);
    free(wc);
}
