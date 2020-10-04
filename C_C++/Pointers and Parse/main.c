/// Author: Damian Chanko 394127


/***********************************************
 * NOTE:
 * This solution use my personal libraries (Words.h, Single.h, List.h).
 * Those libraries were made before task was on MOODLE.
 * Except for Single, I didn't modify any of them,
 * so there are some unused functions like WordsAppend.
 ***********************************************/

#include "BST.h"
#include "Words.h"
#include <string.h>

BST* tree; ///Main tree.

int situation(char *c) /// Checks input command.
{
    if(strcmp(c,"ADD")==0)return 1;
    else if(strcmp(c,"DEL")==0)return 2;
    else if(strcmp(c,"PRINT")==0)return 3;
    else if(strcmp(c,"CHECK")==0)return 4;
    else return -1;
}

int charCheck(char *c) /// Checks if correct string.
{
    size_t len=strlen(c);
    for(unsigned i=0;i<len;i++)
    {
        if(c[i]<33)return 0;
    }
    return 1;
}

void commandMaker(List *L) /// Finds correct command written in input.
{
    elemL *e=L->begin;
    int sit=situation(e->S->c);
    e=e->next;
    elemL *toTree=e;
    while(e!=NULL) ///String check.
    {
        if(charCheck(e->S->c)==0)
        {
            fprintf(stderr,"ERROR\n");
            return;
        }
        e=e->next;
    }
    if(sit==-1)fprintf(stderr,"ERROR\n"); /// Wrond command.
    else if(sit==1) /// ADD command.
    {
        if(L->size==1) /// Not enough arguments.
        {
            fprintf(stderr,"ERROR\n");
            return;
        }
        tree=nodeIns(tree,toTree->S->c);
        toTree->S->c=NULL;
        toTree=toTree->next;
        while(toTree!=NULL)
        {
            BST *curr=LastFound;
            curr->nodeTree=nodeIns(LastFound->nodeTree,toTree->S->c);
            toTree->S->c=NULL;
            toTree=toTree->next;
        }
        printf("OK\n");
    }
    else if(sit==2) /// DEL command.
    {
        printf("OK\n");
        if(toTree==NULL) ///Clear entire universe.
        {
            treeClear(tree);
            tree=NULL;
            return;
        }
        if(toTree->next==NULL) /// Forest deletion.
        {
            tree=nodeDel(tree,toTree->S->c);
            return;
        }
        BST *curr=tree;
        while(toTree->next!=NULL) /// Other.
        {
            curr=nodeFind(curr,toTree->S->c);
            if(curr==NULL)return;
            toTree=toTree->next;
            if(toTree->next!=NULL)curr=curr->nodeTree;
        }
        curr->nodeTree=nodeDel(curr->nodeTree,toTree->S->c);
    }
    else if(sit==3) /// PRINT command.
    {
        if(L->size==4) /// Too many arguments.
        {
            fprintf(stderr,"ERROR\n");
            return;
        }
        BST *curr=tree;
        while(toTree!=NULL)
        {
            curr=nodeFind(curr,toTree->S->c);
            if(curr==NULL)return;
            toTree=toTree->next;
            curr=curr->nodeTree;
        }
        treeWrite(curr);
    }
    else if(sit==4) ///CHECK command.
    {
        if(L->size==1) /// Not enough arguments.
        {
            fprintf(stderr,"ERROR\n");
            return;
        }
        if(strcmp(L->end->S->c,"*")==0) /// Last * situation.
        {
            fprintf(stderr,"ERROR\n");
            return;
        }
        if(treeIter(tree,toTree)==1)printf("YES\n");
        else printf("NO\n");
    }
    return;
}

int main() {
    tree = NULL; /// Universe is empty.
    Words *inp=WordsInit(); /// String for input.
    if(inp==NULL)exit(1);
    int endcode=0; /// Input situation.
    while(endcode==0) {
        endcode = WordsReadLine(inp);
        if (endcode == -2)exit(1); /// Found error during input.
        else {
            if (inp->Size > 0 && inp->Tab[0] == '#') /// Comment.
            {
                WordsClear(inp);
                continue;
            }
            List *L = WordsToList(inp); /// List of inputed words.
            WordsClear(inp);
            if (L == NULL)exit(1);
            else if (endcounter == 1)fprintf(stderr, "ERROR\n"); /// Found NULL in input.
            else if (L->size > 4)fprintf(stderr, "ERROR\n"); /// Too many arguments.
            else if (L->size != 0) /// Something inputted.
            {
                if (endcode == -1)fprintf(stderr, "ERROR\n"); /// Found EOF in wrong place.
                else commandMaker(L);
            }
            ListDel(L); /// This list is no longer needed.
        }
    }
    WordsDel(inp);
    treeClear(tree);

    return 0;
}