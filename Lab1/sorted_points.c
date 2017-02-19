#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "point.h"
#include "sorted_points.h"
#include <math.h>

#define MAXINT 1111111111

typedef struct sorted_points {

    struct Node* head;
//int exist;
	/* you can define this struct to have whatever fields you want. */
} sorted_points;

typedef struct Node {
double x;
double y;
double distance;
struct Node *next;
} Node;

double points_distance(Node* node)
{
    int x, y;
    x = node->x;
    y = node->y;
    node->distance = sqrt(pow(x,2) + pow(y,2));
    return node->distance;
}

Node* set_points(Node* p, double x, double y)
{
    p->x = x;
    p->y = y;
    points_distance(p);
    p->next = NULL;
    return p;
}

sorted_points* sp_init()
{
    sorted_points* sp;
    sp = (sorted_points *)malloc(sizeof(sorted_points));

    Node *L = NULL;
    L = (Node *)malloc(sizeof(Node));
    L->distance = MAXINT;
    L->x = MAXINT;
    L->y = MAXINT;
    L->next = NULL; 

    sp->head = L;
    
    return sp;
}

void sp_destroy(sorted_points *sp)
{
    if(!sp)
        return ; 
    else
    {
        Node* p = sp->head;
        Node* pnext = p->next;

        while(pnext)
        {
            free(p);
            p = pnext;
            pnext = pnext->next;
        }
        free(p);
        free(sp);
        p = NULL;
        sp = NULL;
    }
}

int sp_add_point(sorted_points* sp, double x, double y)
{
    Node* current = NULL;
    Node* new = (Node *)malloc(sizeof(Node));
    set_points(new, x, y);

    // specific case for the head & end
    if (!sp)
        return 0;
    Node* p = sp->head;
    /*if (p->distance == MAXINT && p->x == MAXINT && p->y == MAXINT)
    {
        sp->head = new;
    }*/
    if (p->next==NULL)
        p->next = new;
    else if (p->next->distance > new->distance)
    {
        p = p->next;
        sp->head->next = new;
        new->next = p;
    }
    else
    {   
        p = p->next;
        current = p;
        while(current->next && current->next->distance < new->distance)
        {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
    return 1;

}

int sp_remove_first(sorted_points* sp, struct point *ret)
{
    if(sp==NULL)
        return 0;
    
    Node* p = sp->head->next;

    if(p==NULL){
        return 0;
    }
    else{
        ret->x = p->x;
        ret->y = p->y;
        sp->head->next = p->next;
        free(p);
        p = NULL;
        return 1;
    }
}

int sp_remove_last(sorted_points *sp, struct point *ret)
{
    if(sp==NULL)
        return 0;

    Node* p = sp->head->next;

    if (p==NULL)
    {
        return 0;
    }
    else{
        Node* prev_p = sp->head;
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
        
    }
    return 1;
}


int sp_remove_by_index(sorted_points *sp, int index, struct point *ret)
{
    if(sp==NULL || index<0 )
        return 0;
    Node* p = sp->head->next;
    Node* prev_p = sp->head;
    
    if(p==NULL)
        return 0;
    if(index == 0){
        ret->x = p->x;
        ret->y = p->y;
        prev_p->next = p->next;
        p->next = NULL;
        free(p);
        p = NULL;
        return 1;
    }

    else{
        for (int ii = 0; ii<index-1 && p->next!=NULL; ii++){
            //prev_p = p;
            p = p->next;
        }
        if(p->next==NULL)
            return 0;
        else{
            Node* temp = p->next;
            p->next = temp->next;
            ret->x = temp->x;
            ret->y = temp->y;
            temp->next = NULL;
            free(temp);
            temp = NULL;
            return 1;
        }
    }

}

int sp_delete_duplicates(sorted_points *sp)
{
    //int t = 0;
    int num = 0;
    if(!sp)
        return 0;
    Node *p = sp->head->next;
    if (!p)
        return 0;
    Node *prev_p = sp->head;
    while(p)
    {
        if(p->x == prev_p->x && p->y == prev_p->y)
        {
            prev_p->next = p->next;
            p->next = NULL;
            free(p);
            p = prev_p->next;
            num++;
        }
        else
        {
            prev_p = p;
            p = p->next; 
        }

    }
    return num;
}

void traverse(sorted_points *sp)
{
    Node* p = sp->head->next;
    while (p!=NULL)
    {
        printf("x:%.1f, y:%.1f, distance:%.1f\n", p->x, p->y, p->distance);
        p = p->next;
    }

}
