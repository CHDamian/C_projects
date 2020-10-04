/// Author: Damian Chanko 394127

#include "Single.h"

Single* SinInit(char *c)
{
    Single *S = malloc(sizeof(Single));
    if(S==NULL)return NULL;
    S->c=c;
    return S;
}

void SinDel(Single *S)
{
    free(S->c);
    free(S);
}

void SinSet(Single *S, char *c)
{
    free(S->c);
    S->c=c;
}
void SinTrans(Single *From, Single *To)
{
    SinSet(To,From->c);
    free(From);
}
