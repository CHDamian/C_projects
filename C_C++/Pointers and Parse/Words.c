/// Author: Damian Chanko 394127

#include "Words.h"
#include <ctype.h>
#include <string.h>


Words* WordsInit()
{
    Words* w=malloc(sizeof(Words));
    if(w==NULL)return NULL;
    w->Tab = malloc(16 * sizeof(char));
    if(w->Tab == NULL)
    {
        free(w);
        return NULL;
    }
    w->Size=0;
    w->mSize=16;
    return w;
}

void WordsDel(Words *w)
{
    free(w->Tab);
    free(w);
}

bool WordsInc(Words *w)
{
    w->mSize*=2;
    w->Tab=realloc(w->Tab, w->mSize * sizeof(char));
    if(w->Tab==NULL)return false;
    else return true;
}

bool WordsSet(Words *w, char c, unsigned i)
{
    if(w->Size <= i)return false;
    w->Tab[i]=c;
    return true;
}

char WordsGet(Words *w, unsigned i)
{
    if(w->Size <= i)return 0;
    else return w->Tab[i];
}
bool WordsPush(Words *w, char c)
{
    if(w->Size+1==w->mSize)
    {
        bool b = WordsInc(w);
        if(!b)return false;
    }
    w->Tab[w->Size]=c;
    w->Size++;
    return true;
}

bool WordsAppend(Words *W, Words *Old)
{
    size_t siz = Old->Size;
    char *c = Old->Tab;
    for(unsigned i=0;i<siz;i++)
    {
        if(!WordsPush(W,c[i]))return false;
    }
    return true;
}

void WordsClear(Words *w)
{
    w->Size=0;
}

int WordsReadLine(Words *w)
{
    int x = 1;
    while(x==1)
    {
        int c = getchar();
        if(c == 10) x = 0;
        else if(c==-1)x=-1;
        else if(!WordsPush(w,c))x=-2;
    }
    return x;
}


List* WordsToList(Words *w)
{
    List *L =ListInit();
    if(L==NULL)return NULL;
    Words *temp=WordsInit();
    if(temp==NULL)
    {
        ListDel(L);
        return NULL;
    }
    endcounter=0;
    for(unsigned i=0;i<w->Size;i++)
    {
        if(!isspace(WordsGet(w,i)))
        {
            while(i<w->Size && !isspace(WordsGet(w,i)))
            {
                char c=WordsGet(w,i);
                if(!WordsPush(temp,c))exit(1);
                if(c=='\0')endcounter=1;
                i++;
            }
            if(!WordsPush(temp,'\0'))exit(1);
            char* st=malloc(temp->Size*sizeof(char));
            if(st==NULL)exit(1);
            strcpy(st,temp->Tab);
            Single *S=SinInit(st);
            if(S==NULL)exit(1);
            if(ListPushB(L,S)==0)exit(1);
            WordsClear(temp);
        }
    }
    WordsDel(temp);
    return L;
}
