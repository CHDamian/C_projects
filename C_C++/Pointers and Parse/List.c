/// Author: Damian Chanko 394127

#include "List.h"

elemL* elInit()
{
    elemL *l= malloc(sizeof(elemL));
    if(l==NULL)return NULL;
    l->S=malloc(sizeof(Single));
    if(l->S==NULL)
    {
        free(l);
        return NULL;
    }
    l->S->c=NULL;
    l->next=NULL;
    l->prev=NULL;
    return l;
}

void elDel(elemL *l)
{
    SinDel(l->S);
    if(l->prev!=NULL)l->prev->next=NULL;
    if(l->next!=NULL)l->next->prev=NULL;
    free(l);
}

List* ListInit()
{
    List *L=malloc(sizeof(List));
    if(L==NULL)return NULL;
    L->size=0;
    L->begin=NULL;
    L->end=NULL;
    return L;
}

void ListClear(List *L)
{
    elemL *l=L->begin;
    elemL *pom;
    while (l!=NULL)
    {
        pom=l->next;
        elDel(l);
        l=pom;
    }
}

void ListDel(List *L)
{
    ListClear(L);
    free(L);
}
int ListPushF(List *L, Single *S)
{
    elemL *l=elInit();
    if(l==NULL)return 0;
    SinTrans(S,l->S);
    if (L->size == 0)
    {
        L->begin = l;
        L->end = l;
    }
    else
    {
        L->begin->prev = l;
        l->next = L->begin;
        L->begin = l;
    }
    L->size++;
    return 1;
}

int ListPushB(List *L, Single *S) {
    elemL *l = elInit();
    if (l == NULL)return 0;
    SinTrans(S, l->S);
    if (L->size == 0)
    {
        L->begin = l;
        L->end = l;
    }
    else
    {
        L->end->next = l;
        l->prev = L->end;
        L->end = l;
    }
    L->size++;
    return 1;
}

void ListRemF(List *L)
{
    if(L->size==1)
    {
        elDel(L->begin);
        L->begin=NULL;
        L->end=NULL;
        L->size=0;
        return;
    }
    elemL *l=L->begin;
    L->begin=l->next;
    elDel(l);
    L->size--;
}

void ListRemB(List *L)
{
    if(L->size==1)
    {
        elDel(L->begin);
        L->begin=NULL;
        L->end=NULL;
        L->size=0;
        return;
    }
    elemL *l=L->end;
    L->end=l->prev;
    elDel(l);
    L->size--;
}