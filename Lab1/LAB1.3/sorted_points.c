#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "point.h"
#include "sorted_points.h"
#include "math.h"

struct sorted_points {
double x;
double y;
double distance;
struct sorted_points *next;
//int exist;
	/* you can define this struct to have whatever fields you want. */
};

double points_distance(struct sorted_points* sp)
{
    int x, y;
    x = sp->x;
    y = sp->y;
    sp->distance = sqrt(pow(x,2) + pow(y,2));
    return sp->distance;
}

struct sorted_points * set_points(struct sorted_points *p, double x, double y)
{
    p->x = x;
    p->y = y;
    p->distance = points_distance(p);
    p->next = NULL;
    return p;
}

struct sorted_points *sp_init()
{
    /*struct sorted_points *sp;
    sp = (struct sorted_points *)malloc(sizeof(struct sorted_points));
    assert(sp);
    sp->x = 0.0;
    sp->y = 0.0;
    sp->distance = 0.0;
    sp->next = NULL;
    //sp->exist = 0;
    return sp;*/
    struct sorted_points *L;
    //L = (struct sorted_points *)malloc(sizeof(struct sorted_points));
    //L->next = NULL;
    L = NULL;
    return L;
}

void sp_destroy(struct sorted_points *sp)
{
    if(!sp)
        return ; 
    else
    {
        struct sorted_points *p = sp;
        struct sorted_points *pnext = sp->next;

        while(pnext)
        {
            free(p);
            p = pnext;
            pnext = pnext->next;
        }
        free(p);
    }
}

int sp_add_point(struct sorted_points *sp, double x, double y)
{
    struct sorted_points* current;
    struct sorted_points* new = (struct sorted_points *)malloc(sizeof(struct sorted_points));
    // specific case for the head & end
    set_points(new, x, y);
    if (sp == NULL || sp->distance >= new->distance)
    {
        new->next = sp;
        sp = new;
        return 1;
    }
    else
    {
        current = sp;
        while(current->next && current->next->distance < new->distance)
        {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
        return 1;
    }

    /*
    if(!sp)
        return 0;
    struct sorted_points *p=sp_init();
    p->x = x;
    p->y = y;
    p->distance = sqrt(pow(x,2)+pow(y,2));
    p->exist = 1;
    if (sp->exist == 0)
    {
        sp = p;
        return 1;
    }
    if (sp->distance > p->distance)
    {
        p->next = sp;
        sp = p;
        return 1;
    }
    struct sorted_points *t;
    struct sorted_points *prev_t;
    t = sp;
    prev_t = sp;
    while (t && t->distance < p->distance)
    {
        prev_t = t;
        t = t->next;    
    }
    if (!t)
    {
        prev_t->next = p;
        return 1;
    }
    else
    {
        prev_t->next = p;
        p->next = t;
        return 1;
    }
    return 0;*/

}

int sp_remove_first(struct sorted_points* sp, struct point *ret)
{
    if(sp==NULL)
        return 0;
    struct sorted_points *p = sp->next;
    if(p==NULL){
        free(sp);
        sp = NULL;
    }
    else{
        ret->x = sp->x;
        ret->y = sp->y;
        free(sp);
        sp = p;
    }
    return 1;
}

int sp_remove_last(struct sorted_points *sp, struct point *ret)
{
    if(sp==NULL)
        return 0;
    struct sorted_points* p = sp->next;
    if (p==NULL)
    {
        ret->x = sp->x;
        ret->y = sp->y;
        free(sp);
        sp = NULL;
        return 1;
    }
    struct sorted_points* prev_p = sp;
    while(p->next)
    {
        prev_p = p;
        p = p->next;
    }
    ret->x = p->x;
    ret->y = p->y;
    prev_p->next = NULL;
    free(p);
    p = NULL;
    return 1;
}


int sp_remove_by_index(struct sorted_points *sp, int index, struct point *ret)
{
    if(sp==NULL || index<0)
        return 0;
    struct sorted_points* prev_p = sp;
    struct sorted_points* p = sp->next;
    
    if(p==NULL)
    {
        if (index == 0)
        {
            ret->x = sp->x;
            ret->y = sp->y;
            free(sp);
            sp = NULL;
            return 1;
        }
        else
            return 0;
    }
    int ii;
    for(ii = 1; ii < index-1 && p->next!=NULL; ii++)
    {
        prev_p = p;
        p = p->next;
    }
    if (ii == index-1)
    {
        prev_p->next = p->next;
        ret->x = p->x;
        ret->y = p->y;
        free(p);
        p = NULL;
        return 1;
    }
    return 0;
}


int sp_delete_duplicates(struct sorted_points *sp)
{
    int t = 0;
    if(!sp)
        return 0;
    struct sorted_points *p = sp->next;
    struct sorted_points *prev_p = sp;
    while(p)
    {
        if(p->x == prev_p->x && p->y == prev_p->y)
        {
            prev_p->next = p->next;
            p->next = NULL;
            free(p);
            p = prev_p->next;
            t++;
        }
        else
        {
            prev_p = p;
            p = p->next; 
        }

    }
    return 1;
}


