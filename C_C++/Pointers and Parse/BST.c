/// Author: Damian Chanko 394127

#include "BST.h"
#include <string.h>


BST* nodeInit()
{
    BST *t=malloc(sizeof(BST));
    if(t==NULL)return NULL;
    t->nodeTree=NULL;
    t->lef=NULL;
    t->rig=NULL;
    t->var=NULL;
    return t;
}

void treeClear(BST *t)
{
    if(t==NULL)return;
    treeClear(t->nodeTree);
    treeClear(t->lef);
    treeClear(t->rig);
    free(t->var);
    free(t);
}

BST* nodeIns(BST *t, char *x)
{
    if(t==NULL)
    {
        t=nodeInit();
        if(t==NULL)exit(1);
        t->var=x;
        LastFound=t;
    }
    else if(strcmp(t->var,x) > 0)t->lef=nodeIns(t->lef, x);
    else if(strcmp(t->var,x) < 0)t->rig=nodeIns(t->rig, x);
    else
    {
        free(x);
        LastFound=t;
    }
    return t;
}
void nodePut(BST *t, BST *ins)
{
    if(t->rig==NULL)t->rig=ins;
    else nodePut(t->rig,ins);
}

BST* nodeDel(BST *t, char *x)
{
    if(t==NULL)return NULL;
    else if(strcmp(t->var,x) > 0)t->lef=nodeDel(t->lef, x);
    else if(strcmp(t->var,x) < 0)t->rig=nodeDel(t->rig, x);
    else
    {
        treeClear(t->nodeTree);
        BST *pom;
        if(t->lef==NULL && t->rig==NULL)pom=NULL;
        else if(t->rig==NULL)pom=t->lef;
        else if(t->lef==NULL)pom=t->rig;
        else
        {
            pom=t->lef;
            nodePut(t->lef,t->rig);
        }
        free(t->var);
        free(t);
        t=pom;
    }
    return t;
}

BST* nodeFind(BST *t, char *x)
{
    if(t==NULL)return NULL;
    else if(strcmp(t->var,x) > 0)return nodeFind(t->lef,x);
    else if(strcmp(t->var,x) < 0)return nodeFind(t->rig,x);
    else return t;
}

void treeWrite(BST *t)
{
    if(t==NULL)return;
    treeWrite(t->lef);
    printf("%s\n", t->var);
    treeWrite(t->rig);
}

int treeIter(BST* t, elemL *e)
{
    if(t==NULL || e==NULL)return 0;
    if(strcmp(e->S->c,"*")==0)
    {
        if(treeIter(t->nodeTree,e->next)==1)return 1;
        if(treeIter(t->lef,e)==1)return 1;
        return treeIter(t->rig,e);
    }
    if(strcmp(t->var,e->S->c)==0)
    {
        if(e->next==NULL)return 1;
        return treeIter(t->nodeTree,e->next);
    }
    if(strcmp(t->var,e->S->c) > 0)return treeIter(t->lef,e);
    if(strcmp(t->var,e->S->c) < 0)return treeIter(t->rig,e);
    return 0;
}