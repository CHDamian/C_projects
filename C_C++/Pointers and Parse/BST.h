/// Author: Damian Chanko 394127

#ifndef LIBS_BST_H
#define LIBS_BST_H

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

/***********************************************
 * Implementation of BST tree comparing by chars.
 ***********************************************/

typedef struct BST BST;

struct BST
{
    char* var;
    BST *nodeTree;
    BST *lef;
    BST *rig;
};

BST *LastFound; /// Node found last time by insert.

BST* nodeInit(); /// Node initialization.

void treeClear(BST *t); /// Clear entire tree.

BST* nodeIns(BST *t, char *x); /// Insert node with var x.
void nodePut(BST *t, BST *ins); /// Put node at the end of tree.

BST* nodeDel(BST *t, char *x); /// Delete node with var x.

BST* nodeFind(BST *t, char *x); ///Find node with var x.

void treeWrite(BST *t); /// Print all nodes in-order.

int treeIter(BST* t, elemL *e); /// Used to make checks in Forests exercise.

#endif //LIBS_BST_H
