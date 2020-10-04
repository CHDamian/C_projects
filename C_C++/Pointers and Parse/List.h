/// Author: Damian Chanko 394127

#ifndef LIBS_LIST_H
#define LIBS_LIST_H

#include "Single.h"

typedef struct elemL elemL;

/***********************************************
 * Implementation of double-sided List in c.
 * Using Single as data element.
 ***********************************************/

struct elemL /// List element contains Single.
{
    elemL *prev;
    elemL *next;
    Single *S;
};

elemL* elInit(); /// Initialization of single element.
void elDel(elemL *l); /// Delete element.

typedef struct List List;

struct List /// Main structure.
{
    size_t size;
    elemL *begin;
    elemL *end;
};

List* ListInit(); /// Initialization.
void ListClear(List *L); /// Clear all elements of this list.
void ListDel(List *L); /// Delete.
int ListPushF(List *L, Single *S); /// Push element at the beginning of list.
int ListPushB(List *L, Single *S); /// Push element at the end of list.
void ListRemF(List *L); /// Remove element from the beginning of list.
void ListRemB(List *L);/// Remove element from the end of list.


#endif //LIBS_LIST_H
